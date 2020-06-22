#pragma once
#include <iostream>
#include <string>

template<typename some_type>
class Iterator {
	some_type* cur;//��������� �� ������� ������� ����������
public:
	Iterator(some_type* ptr) :cur(ptr) {}
	//���������� ������� � ��������
	some_type& operator*() { return *cur; }
	some_type* operator->() { return cur; }
	//���������� �������� �� ������ � �������
	Iterator& operator++() { ++cur; return *this; }//next
	//��������� ����������
	bool operator!=(const Iterator& next) { return next.cur != cur; }
	bool operator<(const Iterator& next) { return cur < next.cur; }

};

template<typename some_type>
class conteiner {
	some_type* mass;//��������� � ���� �������
	int size;
public:
	conteiner(int s = 10) :size(10) {
		mass = new some_type[size];
	}
	void show() const {
		for (int i = 0; i < size; ++i)
		{
			std::cout << i << " ";
			std::cout << mass[i];
		}
	}

	Iterator<some_type> start() { return Iterator<some_type>(mass); }//��������� ��������� �� ������ �������
	Iterator<some_type> finish() { return Iterator<some_type>(mass + size); }//��������� ��������� �� ������� �� ���������
	Iterator<some_type> create() { return Iterator<some_type>(mass); }
};

int iter() {
	conteiner<int> ABC;
	ABC.show();
	for (Iterator<int> a = ABC.start(); a != ABC.finish(); ++a)
		std::cout << *a << " ";
	std::cout << std::endl;
	return 0;
}

/*
+
 �������� ������ �������� ������.
 ��������� ����������� ��������� ������� ������ ��������� ������.
 ��������� ������������ ������������ �� ��������� ������ � ������ �������.
- 
 �� ��������, ���� ����� �������� ������� ������.
*/