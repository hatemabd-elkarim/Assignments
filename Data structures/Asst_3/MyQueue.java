package com.mycompany.asst_3;

import java.util.ArrayList;

/*
MyQueue class is implemented using java built in ArrayList class and contains the following methods
- enque(): add an element to the queue
- dequeue(): removes the first element and returns it
- front(): return the first element in a queue without removing it
- isEmpty(): returns true if the queue is empty
- print(): prints the current contents of the queue
*/
public class MyQueue<T> {
    private ArrayList<T> queue;

    public MyQueue() {
        queue = new ArrayList<>();
    }

    // enqueue: Add element to rear
    public void enqueue(T value) {
        queue.add(value);
    }

    // dequeue: Remove and return first element
    public T dequeue() {
        if (queue.isEmpty()) {
            return null;
        }
        return queue.remove(0);
    }

    // front: Return first element without removing
    public T front() {
        if (queue.isEmpty()) {
            return null;
        }
        return queue.get(0);
    }

    // isEmpty: Check if queue is empty
    public boolean isEmpty() {
        return queue.isEmpty();
    }

    // print: Print queue contents
    public void print() {
        System.out.println(queue);
    }
}