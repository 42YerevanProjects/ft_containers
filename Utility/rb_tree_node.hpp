#pragma once

namespace ft
{
    /*
    ==========================
        Rb Node Base Class
    ==========================
    */

    enum rb_tree_color { red = false, black = true };

    struct rb_tree_node_base
    {
        typedef rb_tree_node_base*          base_ptr;
        typedef const rb_tree_node_base*    const_base_ptr;

        base_ptr        parent;
        base_ptr        left;
        base_ptr        right;
        rb_tree_color   color;

        rb_tree_node_base() : parent(), left(), right(), color(black) {}
        rb_tree_node_base(const rb_tree_node_base& other) { *this = other; }

        rb_tree_node_base&  operator=(const rb_tree_node_base& other)
        {
            this->left = other.left;
            this->right = other.right;
            this->parent = other.parent;
            this->color = other.color;

            return (*this);
        }
    };

    /*
    =====================
        RB Node Class
    =====================
    */

    template<typename T>
    struct rb_tree_node : rb_tree_node_base
    {
        typedef rb_tree_node<T>*    link_type;

        T   data;
    };
}
