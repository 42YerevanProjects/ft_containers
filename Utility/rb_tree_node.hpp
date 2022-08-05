#pragma once

namespace ft
{
    /*
    =====================
        RB Node Class
    =====================
    */

    enum rb_tree_color { Red = false, Black = true };
    
    template<typename T>
    struct rb_tree_node
    {
        typedef rb_tree_node<T>*    link_type;

        rb_tree_color   color;
        link_type       parent;
        link_type       left;
        link_type       right;
        T               data;

        rb_tree_node() : color(Black), parent(), left(), right(), data() {}
        rb_tree_node(const rb_tree_node& other) { *this = other; }

        rb_tree_node&   operator=(const rb_tree_node& other)
        {
            this->left = other.left;
            this->right = other.right;
            this->parent = other.parent;
            this->color = other.color;
            this->_data = other._data;

            return (*this);
        }
    };
}
