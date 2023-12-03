#include "tensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct Dimension *tensor_add_dimension(struct NamedTensor *tensor, struct Dimension *dimension) {

}


struct DimensionDef *Dimension(const char* name, uint64_t size) {
    DimensionDef *dimension = (DimensionDef*)malloc(sizeof(DimensionDef));
    if (dimension == NULL) {
        printf("dimension malloc failed!\n");
        exit(0);
    }
    dimension->name = name;
    dimension->size = size;
    return dimension;
}

struct NamedTensor *Tensor() {
    NamedTensor *tensor = (NamedTensor*)malloc(sizeof(NamedTensor));
    if (tensor == NULL) {
        printf("named tensor malloc failed!\n");
        exit(0);
    }

    tensor->addDimension = tensor_add_dimension;
    tensor->data = NULL;
    tensor->dimensions = NULL;

    return tensor;
}