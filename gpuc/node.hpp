#pragma once
#include <iomanip>
#include <memory>
#include "lexeme.hpp"
#include "semantic.hpp"
#include "sequence.hpp"

namespace app::gpuc {

    struct node;

    enum struct recursively_typed {};

    //--------------------------------------------------------------------------

    struct node_ptr : std::unique_ptr<node> {

        node_ptr() = default;
        node_ptr(decltype(nullptr)) {}
        node_ptr(node_ptr&& x) = default;
        node_ptr& operator=(node_ptr&& x) = default;

        node_ptr(semantic, const lexeme* = nullptr, const node* type = nullptr);

        node_ptr(semantic, const lexeme*, recursively_typed);

        operator const node*() const { return std::unique_ptr<node>::get(); }
        operator       node*()       { return std::unique_ptr<node>::get(); }

        const node& operator*() const { return *operator const node*(); }
              node& operator*()       { return *operator       node*(); }

        const node* operator->() const { return operator const node*(); }
              node* operator->()       { return operator       node*(); }
    };

    //--------------------------------------------------------------------------

    using nodes = sequence<node_ptr>;

    //--------------------------------------------------------------------------

    struct node {
        const semantic      semantic {};
        const lexeme* const lexeme   {};
        const node*   const type     {};

    private:
        const node* _parent   {};
        nodes       _children {};

    public:

        node() = delete;
        node(node&&) = delete;
        node& operator=(node&& x) = delete;

        node(
            enum semantic semantic,
            const struct lexeme* lexeme = nullptr,
            const struct node*   type   = nullptr)
        :semantic(semantic)
        ,lexeme(lexeme)
        ,type(type) {}

        node(
            enum semantic semantic,
            const struct lexeme* lexeme,
            recursively_typed)
        :semantic(semantic)
        ,lexeme(lexeme)
        ,type(this) {}

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        auto* parent() const { return _parent; }

        auto& children() const { return _children; }

        auto* type_name() const { return type ? type->lexeme : nullptr; }

        const node* child(size_t i) const {
            if (i < _children.size()) {
                return _children[i];
            } return nullptr;
        }

        const node* child(enum semantic s) const {
            for (auto& child : _children) {
                if (child->semantic == s)
                    return child;
            } return nullptr;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool operator<<(node_ptr&& child) {
            if (child) {
                app_assert(child->_parent == nullptr);
                child->_parent = this;
                _children << std::move(child);
                return true;
            }
            return false;
        }

        bool operator<<(node_ptr& child) {
            return operator<<(std::move(child));
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void write(std::ostream& o) const {
            o << semantic;
            if (lexeme) {
                o << ", " << lexeme->token << ":";
                o << "'" << *lexeme << "'";
            }
            if (type) {
                o << ",\ttype:";
                o << type_name();
            }
            o << "\n";
        }

    };

    //--------------------------------------------------------------------------

    inline node_ptr::node_ptr(
        semantic      semantic,
        const lexeme* lexeme,
        const node*   type)
    :std::unique_ptr<node>(new node(semantic,lexeme,type)) {}

    inline node_ptr::node_ptr(
        semantic      semantic,
        const lexeme* lexeme,
        recursively_typed recurse)
    :std::unique_ptr<node>(new node(semantic,lexeme,recurse)) {}

    //--------------------------------------------------------------------------

    inline bool operator<<(node_ptr& parent, node_ptr&& child) {
        return *parent << std::move(child);
    }

    inline bool operator<<(node_ptr& parent, node_ptr& child) {
        return *parent << std::move(child);
    }

    //--------------------------------------------------------------------------

    inline std::ostream& operator<<(std::ostream& o, const node& root) {
        struct local {
            static
            void indent(std::ostream& o, int depth) {
                while (depth --> 0) o << "    ";
            }
            static
            void write(std::ostream& o, const node& root, const int depth) {
                indent(o,depth);
                root.write(o);
                for (auto& child : root.children())
                    write(o,*child,depth+1);
            }
        };
        local::write(o,root,0);
        return o;
    }

    inline std::ostream& operator<<(std::ostream& o, const node_ptr& root) {
        if (root)
            return o << *root;
        else
            return o << "null";
    }

} // namespace app::gpuc