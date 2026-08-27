//
// Created by JackL on 8/25/26.
//

#include "thread_main.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../scene/scene_types.h"
#include "../lib/pixel.h"
#include "../scene/render.h"

typedef struct {
    int w, h, thread_num, threads;
    Pixel* buffer;
    const SceneInfo *info;
    const List *scene;
    const Camera *cam;
    const CameraSpec *spec;
    int depth;
} ThreadConfig;

void *RenderRows(void *arg) {
    const ThreadConfig *conf = arg;
    SeedRng(conf->thread_num);

    fprintf(stderr, "Thread %d launched.\n", conf->thread_num);

    for (int y = conf->thread_num % conf->threads; y < conf->h; y += conf->threads) {
        for (int x = 0; x < conf->w; x++) {
            const RenderInfo r = {x, y, conf->depth, conf->info, conf->scene, conf->cam, conf->spec};
            conf->buffer[y * conf->w + x] = Render(r);
        }
        if (conf->thread_num == 1) {
            printf("\rProgress: row %d/%d", y, conf->h);
            setvbuf(stdout, NULL, _IONBF, 0);
        }
    }
    return NULL;
}

int WriteFile (const int threads, const int w, const int h, const int depth, const SceneInfo info, const List *scene, const Camera cam, CameraSpec *spec) {

    FILE *f = fopen ("out.ppm", "w");
    if (!f) {perror("fopen failed"); return 1;}

    fprintf(f, "P3\n%d %d\n255\n", w, h);

    Pixel *buffer = malloc((size_t) w * h * sizeof(Pixel));
    pthread_t *threads = malloc((size_t) num_threads*sizeof(pthread_t));
    ThreadConfig *configs = malloc((size_t) num_threads*sizeof(ThreadConfig));

    if (!buffer || !threads || !configs) {
        perror("Malloc failed for buffer, threads, or configs!");
        free(threads);
        free(configs);
        free(buffer);
        return 1;
    }

    // Populate the thread configs, create the threads
    for (int thr=0; thr<num_threads; thr++) {
        configs[thr] = (ThreadConfig) {
            .w = w, .h = h, .thread_num = thr+1, .threads = num_threads,
            .buffer = buffer,
            .info = &info, .scene = scene, .cam=&cam, .spec=spec,
            .depth = depth
        };

        pthread_create(&threads[thr], NULL, RenderRows, &configs[thr]);
    }

    // Wait for the threads to finish
    for (int thr=0; thr<num_threads; thr++) {
        const pthread_t thread = threads[thr];
        pthread_join(thread, NULL);
    }

    // Free threads and configs
    free(threads);
    free(configs);

    // Write the file
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            const Pixel p = buffer[y*w+x];
            fprintf(f, "%d %d %d\n", p.r, p.g, p.b);
        }
    }

    free(buffer);

    fclose(f);

    return 0;
}