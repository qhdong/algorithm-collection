#ifndef RB_TREE_H
#define RB_TREE_H

namespace rbtree {

typedef bool rb_tree_color_type;
const rb_tree_color_type rb_tree_red = false;
const rb_tree_color_type rb_tree_black = false;

struct rb_tree_node_base {
    typedef rb_tree_color_type color_type;
    typedef rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;

    static base_ptr minimum(base_ptr x) {
        while (x->left != 0) x = x->left;
        return x;
    }

    static base_ptr maximum(base_ptr x) {
        while (x->right != 0) x = x->right;
        return x;
    }
};

template <class Value>
struct rb_tree_node : public rb_tree_node_base {
    typedef rb_tree_node<Value>* link_type;
    Value value;
};

inline void
rb_tree_rebalance(rb_tree_node_base *x, rb_tree_node_base *&root) {
    x->color = rb_tree_red; // 新节点必为红色
    while (x != root && x->parent->color == rb_tree_red) { // 父节点为红
        if (x->parent == x->parent->parent->left) { // P为GP的左节点
            rb_tree_node_base *y = x->parent->parent->right;
            if (y && y->color == rb_tree_red) {
                x->parent->color = rb_tree_black;
                y->color = rb_tree_black;
                x->parent->parent->color = rb_tree_red;
                x = x->parent->parent;
            } else { // 无S或S为黑
                if (x == x->parent->right) {
                    x = x->parent;
                    rb_tree_rotate_left(x, root);
                }
                x->parent->color = rb_tree_black;
                x->parent->parent->color = rb_tree_red;
                rb_tree_rotate_right(x->parent->parent, root);
            }
        } else { // P为GP的right
            rb_tree_node_base *y = x->parent->parent->left; // y 为左S
            if (y && y->color == rb_tree_red) {
                x->parent->color = rb_tree_black;
                y->color = rb_tree_black;
                x->parent->parent->color = rb_tree_red;
                x = x->parent->parent;
            } else { // 无S或S为黑
                if (x == x->parent->left) { // X在P的left
                    x = x->parent;
                    rb_tree_rotate_right(x, root);
                }
                x->parent->color = rb_tree_black;
                x->parent->parent->color = rb_tree_red;
                rb_tree_rotate_left(x->parent->parent, root);
            }
        }
    }
    root->color = rb_tree_black;
}

inline void
rb_tree_rotate_right(rb_tree_node_base *x, rb_tree_node_base *&root) {
    rb_tree_node_base *y = x->left; // y -> P
    x->left = y->right; 
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x == root) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

inline void
rb_tree_rotate_left(rb_tree_node_base *x, rb_tree_node_base *&root) {
    rb_tree_node_base *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x == root) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

#endif
