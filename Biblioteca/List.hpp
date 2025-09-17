#pragma once

#include <iostream>
#include <new>

template <typename T>
struct Node
{
    Node() : Next(nullptr) {}
    Node(const T& value, Node* next = nullptr) : Value(value), Next(next) {}
    Node(T&& value, Node* next = nullptr) : Value(value), Next(next) {}

    T Value;
    Node *Next;
};

template<typename T>
class List
{
public:
    using ValueType = T;
    using NodeType = Node<ValueType>;

    List() : m_Head(nullptr), m_Size(0) {}
    ~List()
    {
        if(m_Head == nullptr)
            return;

        NodeType* temp;

        while(m_Head != nullptr)
        {
            temp = m_Head;
            m_Head = m_Head->Next;
            delete temp;
        }
    }

    bool Empty() const noexcept
    {
        return m_Size == 0;
    }

    size_t Size() const noexcept
    {
        return m_Size;
    }

    T& Front() noexcept
    {
        return m_Head->Value;
    }

    const T& Front() const noexcept
    {
        return m_Head->Value;
    }

    void PushFront(const T& value)
    {
        NodeType* newNode = new(std::nothrow) NodeType(value, m_Head);

        if(newNode == nullptr)
        {
            std::cout << "Failed to allocate space for a new node";
            std::abort();
        }

        ++m_Size;
        m_Head = newNode;
    }

    void PushFront(T&& value)
    {
        NodeType* newNode = new(std::nothrow) NodeType(value, m_Head);

        if(newNode == nullptr)
        {
            std::cout << "Failed to allocate space for a new node";
            std::abort();
        }

        ++m_Size;
        m_Head = newNode;
    }

    void PopFront()
    {
        if(m_Head == nullptr)
            return;

        NodeType* temp = m_Head;
        m_Head = m_Head->Next;
        delete temp;

        --m_Size;
    }

    template<typename CmpFunc>
    bool Erase(const CmpFunc& cmpFunc, const T& value)
    {
        if(m_Size == 0)
            return false;

        if(cmpFunc(m_Head->Value, value))
        {
            PopFront();
            return true;
        }

        NodeType* curr = m_Head;

        while(curr->Next != nullptr)
        {
            if(cmpFunc(curr->Next->Value, value))
            {
                NodeType* temp = curr->Next;
                curr->Next = temp->Next;
                delete temp;
                --m_Size;
                return true;
            }

            curr = curr->Next;
        }

        return false;
    }

    template<typename Func>
    void ForEach(const Func& func)
    {
        NodeType* curr = m_Head;

        while(curr != nullptr)
        {
            func(curr->Value);
            curr = curr->Next;
        }
    }

    template<typename Func>
    void ForEach(const Func& func) const
    {
        NodeType* curr = m_Head;

        while(curr != nullptr)
        {
            func(curr->Value);
            curr = curr->Next;
        }
    }

    template<typename CmpFunc>
    T* Search(const CmpFunc& cmpFunc, const T& value) const
    {
        NodeType* curr = m_Head;

        while(curr != nullptr)
        {
            if(cmpFunc(curr->Value, value))
                return &curr->Value;

            curr = curr->Next;
        }

        return nullptr;
    }

    template<typename CmpFunc>
    void Sort(const CmpFunc& cmpFunc)
    {
        m_Head = SortInternal(m_Head, cmpFunc);
    }

private:
    static NodeType* Split(NodeType* head)
    {
        if(head == nullptr)
            return nullptr;

        NodeType* slow = head;
        NodeType* fast = head->Next;

        while(fast != nullptr && fast->Next != nullptr)
        {
            fast = fast->Next->Next;
            slow = slow->Next;
        }

        NodeType* temp = slow->Next;
        slow->Next = nullptr;
        return temp;
    }

    template<typename CmpFunc>
    static NodeType* Merge(NodeType* a, NodeType* b, const CmpFunc& cmpFunc)
    {
        if(a == nullptr)
            return b;

        if(b == nullptr)
            return a;

        NodeType* result;

        if(cmpFunc(a->Value, b->Value))
        {
            result = a;
            result->Next = Merge(a->Next, b, cmpFunc);
        }
        else
        {
            result = b;
            result->Next = Merge(a, b->Next, cmpFunc);
        }

        return result;
    }

    template<typename CmpFunc>
    static NodeType* SortInternal(NodeType* head, const CmpFunc& cmpFunc)
    {
        if(head == nullptr || head->Next == nullptr)
            return head;

        NodeType* mid = Split(head);

        head = SortInternal(head, cmpFunc);
        mid = SortInternal(mid, cmpFunc);

        return Merge(head, mid, cmpFunc);
    }

    NodeType* m_Head;
    size_t m_Size;
};
