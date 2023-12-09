#include "model.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Layer *Conv2D(uint64_t filters, TupleU64 *kernel_size, ActivationType actv) {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("conv2d layer alloc failed!\n");
        exit(1);
    }

    layer->activation = actv;

    return layer;
}

struct Layer *MaxPooling2D(TupleU64 *kernel_size) {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("max polling layer alloc failed!\n");
        exit(1);
    }

    return layer;
}


struct Layer *Flatten() {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("flatten layer alloc failed!\n");
        exit(1);
    }

    return layer;
}

struct Layer *Dense(uint64_t units, ActivationType actv) {
    struct Layer *layer = (struct Layer*)malloc(sizeof(Layer));
    if (layer == NULL) {
        printf("dense layer alloc failed!\n");
        exit(1);
    }

    return layer;
}

struct Layer* model_add_layer(struct NNModel *model, struct Layer *layer) {

}

struct NNModel* model_compile(struct NNModel *model, OptmizerType optmizer, LossFuncType lossFunc) {

}

struct NNModel* model_fit(struct NNModel *model, struct Tensor *data, uint64_t epochs, uint64_t batchSize, float validationSplit) {

}

struct NNModel* model_evaluate(struct NNModel *model) {

}

struct NNModel *SequentialModel() {
    struct NNModel *model = (struct NNModel*)malloc(sizeof(NNModel));
    if (model == NULL) {
        printf("model alloc failed!\n");
        exit(1);
    }

    model->layers = NULL;
    model->addLayer = model_add_layer;
    model->compile = model_compile;
    model->fit = model_fit;
    model->evaluate = model_evaluate;

    return model;
}