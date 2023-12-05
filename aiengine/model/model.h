#ifndef __MODEL_H__
#define __MODEL_H__

typedef enum {
    RELU,
    SOFTMAX,
} ActivationType;

typedef struct Layer {
    ActivationType activation;
} Layer;

struct Layer *Conv2D(ActivationType actv);

struct Layer *MaxPooling2D();

struct Layer *Flatten();

struct Layer *Dense(ActivationType actv);

typedef struct Layer* (*AddLayer)(struct NNModel *model, struct Layer *layer);

typedef struct NNModel {
    Layer *layers;
    AddLayer addLayer;
} NNModel;

struct NNModel *SequentialModel();

#endif /* __MODEL_H__ */