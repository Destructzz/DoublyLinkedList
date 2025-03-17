#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>


namespace Destruct {
	template<typename T>
	class List {
	protected:
		class Node {
		public:
			Node() = default;
			Node(T value) : value(value), next(nullptr), previous(nullptr) {};
			Node(const Node* node) : value(node->value), next(node->next), previous(previous) {};

			T value;
			Node* next;
			Node* previous;

		};

		size_t main_size = 0;

		Node* head;
		Node* tail;

	public:

		class iterator {
		public:

			iterator(Node* node);

			iterator& operator++(int);

			iterator& operator--(int);

			iterator& operator++();

			iterator& operator--();

			iterator operator+(int count);

			bool operator!=(const iterator& other) const;

			bool operator==(const iterator& other) const;

			T& operator*();

			friend class List<T>;

		protected:

			Node* get_node();

			Node* current;
		};


		List();  // Конструктор

		List(size_t count);

		List(size_t count, const T& value);

		List(std::initializer_list<T> init);

		List(const List<T>& other);

		List(List<T>&& other);

		~List();

		void push_back(T value);  // Добавление элемента в конец

		void push_front(T value);

		void pop_back();

		void pop_front();

		bool empty() const;

		T& back() const;

		T& front() const;

		size_t size() const;

		T& at(size_t index) const;  // Доступ к элементу по индексу

		iterator begin();

		iterator end();

		void erase(iterator it);

		void insert(iterator it, T value);
	};

	// Реализация конструктора
	template<typename T>
	List<T>::List() : main_size(0), head(nullptr), tail(nullptr) {}

	template<typename T>
	inline List<T>::List(size_t count) : main_size(0), head(nullptr), tail(nullptr)
	{
		for (int i = 0; i < count; i++)
			this->push_back(T());
	}

	template<typename T>
	inline List<T>::List(size_t count, const T& value) : main_size(0), head(nullptr), tail(nullptr)
	{
		for (size_t i = 0; i < count; i++)
			this->push_back(T(value));
	}

	template<typename T>
	inline List<T>::List(std::initializer_list<T> init) : main_size(0), head(nullptr), tail(nullptr)
	{
		for (auto& el : init) {
			this->push_back(el);
		}
	}

	template<typename T>
	inline List<T>::List(const List<T>& other) : main_size(0), head(nullptr), tail(nullptr)
	{
		std::cout << "copy active\n";
		for (size_t i = 0; i < other.size(); i++) {
			this->push_back(other.at(i));
		}
	}

	template<typename T>
	inline List<T>::List(List<T>&& other) : main_size(other.main_size), head(other.head), tail(other.tail)
	{
		other.main_size = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}

	template<typename T>
	inline List<T>::~List()
	{
		while (head != nullptr) {
			this->pop_front();
		}
	}

	// Реализация метода push_back
	template<typename T>
	void List<T>::push_back(T value) {
		if (main_size == 0) {
			tail = head = new Node(value);
			main_size++;
			return;
		}
		tail->next = new Node(value);
		tail->next->previous = tail;
		tail = tail->next;

		main_size++;
	}

	template<typename T>
	inline void List<T>::push_front(T value)
	{
		if (main_size == 0) {
			head = new Node(value);
			tail = head;
			main_size++;
			return;
		}

		head->previous = new Node(value);
		head->previous->next = head;

		head = head->previous;

		main_size++;
	}

	template<typename T>
	void List<T>::pop_back() {
		if (main_size == 0) {
			return;
		}

		if (main_size == 1) {
			delete tail;
			head = tail = nullptr;
			main_size--;
			return;
		}

		Node* current = tail;
		tail = tail->previous;

		if (tail != nullptr) {
			tail->next = nullptr;
		}

		delete current;
		main_size--;
	}



	template<typename T>
	inline void List<T>::pop_front()
	{
		if (main_size == 0)
			return;

		if (main_size == 1) {
			delete head;
			head = tail = nullptr;
			main_size--;
			return;
		}

		Node* current = head->next;

		delete head;

		head = current;

		main_size--;
	}

	template<typename T>
	inline bool List<T>::empty() const
	{
		return !main_size;
	}

	template<typename T>
	inline T& List<T>::back() const
	{
		return tail->value;
	}

	template<typename T>
	inline T& List<T>::front() const
	{
		return head->value;
	}

	template<typename T>
	inline size_t List<T>::size() const
	{
		return main_size;
	}




	// Реализация метода at
	template<typename T>
	T& List<T>::at(size_t index) const {
		if (index >= main_size) {
			throw std::out_of_range("Index out of range");
		}

		Node* current;

		if (index > main_size / 2) {
			current = head;

			for (size_t i = 0; i < index; ++i) {
				current = current->next;
			}
		}
		else {
			current = tail;

			for (int i = 0; i < (main_size - 1) - index; i++) {
				current = current->previous;
			}
		}


		return current->value;
	}

	template<typename T>
	inline typename List<T>::iterator List<T>::begin()
	{
		return iterator(head);
	}

	template<typename T>
	inline typename List<T>::iterator List<T>::end()
	{
		return iterator(nullptr);
	}

	template<typename T>
	inline void List<T>::erase(iterator it)
	{
		if (it == this->end()) {
			throw std::out_of_range("iterator out of range");
			return;
		}

		if (it == this->begin()) {
			this->pop_front();
			return;
		}

		if (it + 1 == this->end()) {
			this->pop_back();
			return;
		}


		Node* current = it.get_node();

		Node* temp = current->previous;

		temp->next = current->next;

		current->next->previous = temp;

		delete current;
		current = nullptr;

		main_size--;
	}

	template<typename T>
	inline void List<T>::insert(iterator it, T value)
	{
		if (it == this->end()) {
			this->push_back(value);
			return;
		}

		if (it == this->begin()) {
			this->push_front(value);
			return;
		}

		Node* current = it.get_node();

		Node* new_node = new Node(value);

		Node* prev_node = current->previous;

		prev_node->next = new_node;

		new_node->next = current;

		current->previous = new_node;

		new_node->previous = prev_node;


		main_size++;
	}



	//iterator

	template<typename T>
	inline List<T>::iterator::iterator(Node* node) : current(node)
	{

	}

	template<typename T>
	inline T& List<T>::iterator::operator*()
	{
		return current->value;
	}

	template<typename T>
	inline typename List<T>::Node* List<T>::iterator::get_node()
	{
		return current;
	}

	template<typename T>
	inline typename List<T>::iterator& List<T>::iterator::operator++(int)
	{
		current = current->next;
		return *this;
	}

	template<typename T>
	inline typename List<T>::iterator& List<T>::iterator::operator--(int)
	{
		current = current->previous;
		return *this;
	}

	template<typename T>
	inline typename List<T>::iterator& List<T>::iterator::operator++()
	{
		current = current->next;
		return *this;
	}

	template<typename T>
	inline typename List<T>::iterator& List<T>::iterator::operator--()
	{
		current = current->previous;
		return *this;
	}

	template<typename T>
	inline typename List<T>::iterator List<T>::iterator::operator+(int count)
	{
		iterator temp = *this;


		for (int i = 0; i < count; i++) {
			if (temp != nullptr) {
				++temp;
			}
			else {
				break;
			}
		}
		return temp;
	}



	template<typename T>
	inline bool List<T>::iterator::operator!=(const typename List<T>::iterator& other) const
	{
		return current != other.current;
	}

	template<typename T>
	inline bool List<T>::iterator::operator==(const iterator& other) const
	{
		return current == other.current;
	}
}



#endif  // LIST_H