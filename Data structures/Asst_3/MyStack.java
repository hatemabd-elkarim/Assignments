package com.mycompany.asst_3;

import java.util.Collections;
import java.util.LinkedList;

/*
Mystack class is implemented using java built in LinkedList class and contains the following methods
- pop(): removes the top element and returns it
- push(): add an element to the stack
- peak(): return the first element in a stack without removing it
- isEmpty(): returns true if the stack is empty
- reverse(): reverses the currnt stack elements order

*/
public class MyStack<T> {
    private LinkedList<T> stack;

    public MyStack() {
        stack = new LinkedList<>();
    }

    // Push: Add element to the top
    public void push(T value) {
        stack.addFirst(value);
    }

    // Pop: Remove and return top element
    public T pop() {
        if (stack.isEmpty()) {
            return null;
        }
        return stack.removeFirst();
    }

    // Peak: Return top element without removing
    public T peek() {
        if (stack.isEmpty()) {
            return null;
        }
        return stack.getFirst();
    }

    // isEmpty(): Check if stack is empty
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    // reverse: Reverse stack order
    public void reverse() {
        Collections.reverse(stack);
    }
    
     // print: Print queue contents
    public void print() {
        System.out.println(stack);
    }
}
