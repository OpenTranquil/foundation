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
    struct ComputeNode *parent;

    double grad;
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

double backward(ComputeNode *node) {
    ComputeNode *cur = node;
    while (cur != NULL) {
        if (cur->type == VARIABLE) {
            cur->grad = 1.0f;
        }
        if (cur->type == CONSTANT) {
            printf("cannot compute grad for constant!\n");
            exit(1);
        }
        if (cur->type == BINARY_OPERATOR) {
            cur->operator.op->backward(cur);
        }
        if (cur->parent == NULL) {
            return cur->grad;
        }
        cur = cur->parent;
    }
}

double op_pow_forword(struct ComputeNode *node) {
    ComputeNode *left = node->operator.left;
    ComputeNode *right = node->operator.right;
    return pow(forword(left), forword(right));
}

double op_pow_backword(struct ComputeNode *node) {
    ComputeNode *left = node->operator.left;
    ComputeNode *right = node->operator.right;
    double grad = forword(right) * forword(left) * left->grad;
    node->grad = grad;
    return grad;
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
    ComputeNode *left = node->operator.left;
    double grad = 1.0f * left->grad;
    node->grad = grad;
    return grad;
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
    ComputeNode *right = node->operator.right;
    ComputeNode *left = node->operator.left;
    double grad = forword(right) * left->grad;
    node->grad = grad;
    return grad;
}

OperatorFunc op_mul = {
    .type = MUL,
    .forword = op_mul_forword,
    .backward = op_mul_backword,
};

// f = (ax + b)^2
// Z = ax
// Y = Z + b
// F = Y ^ 2

// fx' = FY'YZ'Zx'
// fx' = 2Y * 1 * a
// fx' = 2(ax +b) * 1 * a
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
    node_2.grad = 1.0f;
    node_a.type = CONSTANT;
    node_a.constant.val = a;
    node_a.grad = 1.0f;
    node_x.type = VARIABLE;
    node_x.variable.val = x;
    node_x.grad = 1.0f;
    node_b.type = CONSTANT;
    node_b.constant.val = b;
    node_b.grad = 1.0f;

    // operator node init
    node_pow.type = BINARY_OPERATOR;
    node_pow.grad = 1.0f;
    node_pow.operator.left = &node_add;
    node_pow.operator.right = &node_2;
    node_pow.operator.op = &op_pow;

    node_add.type = BINARY_OPERATOR;
    node_add.grad = 1.0f;
    node_add.operator.left = &node_mul;
    node_add.operator.right = &node_b;
    node_add.operator.op = &op_add;

    node_mul.type = BINARY_OPERATOR;
    node_mul.grad = 1.0f;
    node_mul.operator.left = &node_x;
    node_mul.operator.right = &node_a;
    node_mul.operator.op = &op_mul;

    node_2.parent = &node_pow;
    node_a.parent = &node_mul;
    node_x.parent = &node_mul;
    node_b.parent = &node_add;
    node_add.parent = &node_pow;
    node_mul.parent = &node_add;

    printf("ACTUAL val: %f, grad:%f\n", forword(&node_pow), backward(&node_x));
    return 0;
}