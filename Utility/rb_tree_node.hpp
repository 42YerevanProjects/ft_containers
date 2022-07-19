#pragma once

namespace ft
{
    /*
    ==========================
        Rb Node Base Class
    ==========================
    */

    enum rb_tree_color { Red = false, Black = true };

    struct rb_tree_node_base
    {
        typedef rb_tree_node_base*          base_ptr;
        typedef const rb_tree_node_base*    const_base_ptr;

        rb_tree_color   color;
        base_ptr        parent;
        base_ptr        left;
        base_ptr        right;


        rb_tree_node_base() : left(), right(), parent(), color(Black) {}
        rb_tree_node_base(const rb_tree_node_base& other) { *this = other; }

        rb_tree_node_base&  operator=(const rb_tree_node_base& other)
        {
            this->left = other.left;
            this->right = other.right;
            this->parent = other.parent;
            this->color = other.color;

            return (*this);

        }

        static base_ptr            minimum(base_ptr x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static const_base_ptr      minimum(const_base_ptr x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static base_ptr            maximum(base_ptr x)
        {
            while (x->right != 0)
                x = x->right;
            return x;
        }

        static const_base_ptr      maximum(const_base_ptr x)
        {
            while (x->right != 0)
                x = x->right;
            return x;
        }
    };

    /*
    =====================
        Rb Node Class
    =====================
    */
    
    template<typename T>
    struct rb_tree_node : rb_tree_node_base
    {
        typedef rb_tree_node<T>*    link_type;

        T   value;

        rb_tree_node() : rb_tree_node_base() {}
        rb_tree_node(const rb_tree_node& other) : rb_tree_node_base(other) { value = other.value; }

        rb_tree_node&   operator=(const rb_tree_node& other)
        {
            this->left = other.left;
            this->right = other.right;
            this->parent = other.parent;
            this->color = other.color;
            this->value = other.value;

            return (*this);
        }
    };
}
