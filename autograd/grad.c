#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef enum NodeType {
    VARIABLE = 0,
    CONSTANT,
    BINARY_OPERATOR,
} NodeType;

typedef enum OperatorType {
    MUL = 0,
    ADD,
    DIV,
    POW,
    LOG,
    LN,
} OperatorType;

typedef struct OperatorFunc {
    OperatorType type;
    double (*forword)(struct ComputeNode *node);
    double (*backward)(struct ComputeNode *node);
} OperatorFunc;

typedef struct ComputeNode {
    NodeType type;

    union {
        struct {
            struct Node *left;
            struct Node *right;
            OperatorFunc *op;
        } operator;
        struct {
            double val;
        } variable;
        struct {
            double val;
        } constant;
    };
} ComputeNode;

double forword(ComputeNode *node) {
    if (node->type == VARIABLE) {
        return node->variable.val;
    }
    if (node->type == CONSTANT) {
        return node->constant.val;
    }
    return node->operator.op->forword(node);
}

double op_pow_forword(struct ComputeNode *node) {
    ComputeNode *left = node->operator.left;
    ComputeNode *right = node->operator.right;
    return pow(forword(left), forword(right));
}

double op_pow_backword(struct ComputeNode *node) {
    return 0; //TODO
}

OperatorFunc op_pow = {
    .type = POW,
    .forword = op_pow_forword,
    .backward = op_pow_backword,
};

double op_add_forword(struct ComputeNode *node) {
    ComputeNode *left = node->operator.left;
    ComputeNode *right = node->operator.right;
    return forword(left) + forword(right);
}

double op_add_backword(struct ComputeNode *node) {
    return 0; //TODO
}

OperatorFunc op_add = {
    .type = ADD,
    .forword = op_add_forword,
    .backward = op_add_backword,
};

double op_mul_forword(struct ComputeNode *node) {
    ComputeNode *left = node->operator.left;
    ComputeNode *right = node->operator.right;

    return forword(left) * forword(right);
}

double op_mul_backword(struct ComputeNode *node) {
    return 0; //TODO
}

OperatorFunc op_mul = {
    .type = MUL,
    .forword = op_mul_forword,
    .backward = op_mul_backword,
};

double backward(ComputeNode *node) {
    if (node->type == VARIABLE) {
        return 1;
    }
    if (node->type == CONSTANT) {
        return 0;
    }
    return node->operator.op->forword(node);
}

// f = (ax + b)^2
// Z = (ax + b)
// F = Z^2

// fx' = FZ'Zx'
// fx' = 2Za
// fx' = 2(ax+b)a

double fx(double x, double a, double b) {
    double val = pow((a * x + b), 2);
    return val;
}

double fdx(double x, double a, double b) {
    double grad = 2.0f * (a * x + b) * a;
    return grad;
}

int main(int argc, char *argv[]) {
    double a = 5.1f;
    double x = 6.3f;
    double b = 2.1f;
    printf("a:%f, b:%f, x:%f \n", a, b, x);
    double exp_val = fx(x, a, b);
    double exp_grad = fdx(x, a, b);
    printf("EXPECTED val:%f, grad:%f\n", exp_val, exp_grad);

    ComputeNode node_a;
    ComputeNode node_mul;
    ComputeNode node_x;
    ComputeNode node_add;
    ComputeNode node_b;
    ComputeNode node_pow;
    ComputeNode node_2;

    // variable node init
    node_2.type = CONSTANT;
    node_2.constant.val = 2.0f;
    node_a.type = CONSTANT;
    node_a.constant.val = a;
    node_x.type = VARIABLE;
    node_x.variable.val = x;
    node_b.type = CONSTANT;
    node_b.constant.val = b;

    // operator node init
    node_pow.type = BINARY_OPERATOR;
    node_pow.operator.left = &node_add;
    node_pow.operator.right = &node_2;
    node_pow.operator.op = &op_pow;

    node_add.type = BINARY_OPERATOR;
    node_add.operator.left = &node_mul;
    node_add.operator.right = &node_b;
    node_add.operator.op = &op_add;

    node_mul.type = BINARY_OPERATOR;
    node_mul.operator.left = &node_a;
    node_mul.operator.right = &node_x;
    node_mul.operator.op = &op_mul;

    printf("ACTUAL val: %f\n", forword(&node_pow));
    printf("ACTUAL grad: %f\n", backward(&node_x));
    return 0;
}