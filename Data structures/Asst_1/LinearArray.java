package com.mycompany.asst_1;
/*
Design a class LinearArray which is represented by 2 instance variables: an array of integers and an integer variable 
representing the total number of elements inserted in the array. Implement the class LinearArray with the 
following instance methods: 
    a) Write a method void insertLast(int x) which inserts a new element at the end of the array. 
    b) Write a method void insertFirst(int x) which inserts a new element at the beginning of the array. 
    c) Write a method int linearSearch(int x) which returns the position of a specific element and -1 if 
    it is not found. 
    d) Write a method void delete(int x) which deletes a specific element from the array.
*/
public class LinearArray {
    int[] arr;
    int size;

    public LinearArray() {
        this(10);
    }
    
    public LinearArray(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException("Capacity must be positive"); 
        } 
        this.arr = new int[capacity];
    }
    
    
    void insertLast(int x) {
        if (size >= arr.length) {
            resize();
        }
        arr[size] = x;
        size++;   
    }
    
    
    void insertFirst(int x) {
        if (size >= arr.length) {
            resize();
        }
        for(int i = size; i >= 1; i--) { // shift elements by one cell
            arr[i] = arr[i-1];
        }
        arr[0] = x;
        size++;   
    }
    
    
    int linearSearch(int x) {
        int index = -1;
        for(int i = 0; i < size; i++) {
            if(arr[i] == x) {
                index = i;
                break;
            }
        }
        return index;
    }
    
    
    void delete(int x) {
        int index = linearSearch(x);
        if(index == -1) {
            return;
        }
        for(int i = index; i < size-1; i++) {
            arr[i]=arr[i+1];
        }
        size--;
    }
    
    
    void resize() {
        int[] newarr = new int[arr.length*2];
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
            s.append(arr[i]);
            if (i < size - 1) {
                s.append(", ");
            }
        }
        s.append("]");
        return s.toString();
    }
}
