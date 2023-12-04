#include "model.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Layer *Conv2D(ActivationType type) {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("conv2d layer alloc failed!\n");
        exit(1);
    }

    layer->activation = type;

    return layer;
}

struct Layer *MaxPolling() {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("max polling layer alloc failed!\n");
        exit(1);
    }

    return layer;
}

struct Layer* model_add_layer(struct NNModel *model, struct Layer *layer) {

}

struct NNModel *Model() {
    struct NNModel *model = (struct NNModel*)malloc(sizeof(NNModel));
    if (model == NULL) {
        printf("model alloc failed!\n");
        exit(1);
    }

    model->layers = NULL;
    model->addLayer = model_add_layer;

    return model;
}