package com.mycompany.asst_1;
/*
How would you change your implementation of the previous exercise to store Objects of type Student instead of 
integers in your unsorted array? 
    a) Define a class Student to represent a Student in terms of his/her first name, last name and id. 
    b) Define a class LinearArrayStudents to represent an unsorted array of students. Add methods to insert, 
    search and delete students from the array.
*/
public class LinearArrayStudents {
    Student[] arr;
    int size;

    public LinearArrayStudents() {
        this(10);
    }
    
    public LinearArrayStudents(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException("Capacity must be positive"); 
        } 
        this.arr = new Student[capacity];
    }
    
    
    void insertLast(Student x) {
        if (size >= arr.length) {
            resize();
        }
        arr[size] = x;
        size++;   
    }
    
    
    void insertFirst(Student x) {
        if (size >= arr.length) {
            resize();
        }
        for(int i = size; i >= 1; i--) { // shift elements by one cell
            arr[i] = arr[i-1];
        }
        arr[0] = x;
        size++;   
    }
    
    
    int linearSearch(int id) {
        int index = -1;
        for(int i = 0; i < size; i++) {
            if(arr[i].id == id) {
                index = i;
                break;
            }
        }
        return index;
    }
    
    
    void delete(int id) {
        int index = linearSearch(id);
        if(index == -1) {
            return;
        }
        for(int i = index; i < size-1; i++) {
            arr[i]=arr[i+1];
        }
        size--;
    }
    
    
    void resize() {
        Student[] newarr = new Student[arr.length*2];
        for(int i = 0; i < arr.length; i++) {
            newarr[i] = arr[i];
        }
        arr = newarr;
    }
    
    @Override
    public String toString() {
        if (size == 0) {
            return "Empty array";
        }

        StringBuilder s = new StringBuilder("[");
        for (int i = 0; i < size; i++) {
            s.append(arr[i].fname+" "+arr[i].lname);
            if (i < size - 1) {
                s.append(", ");
            }
        }
        s.append("]");
        return s.toString();
    }
}
