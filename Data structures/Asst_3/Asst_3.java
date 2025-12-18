package com.mycompany.asst_3;

public class Asst_3 {

    public static void main(String[] args) {
        // Stack tests
        System.out.println("Testing MyStack:");
        MyStack<Integer> stack = new MyStack<>();

        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.print();

        System.out.println("Peek: " + stack.peek());
        System.out.println("Pop: " + stack.pop());
        stack.print();

        stack.reverse();
        System.out.print("After reverse: ");
        stack.print();

        System.out.println("Is stack empty? " + stack.isEmpty());

        System.out.println();
        
        // Queue tests
        System.out.println("Testing MyQueue:");
        MyQueue<String> queue = new MyQueue<>();

        queue.enqueue("A");
        queue.enqueue("B");
        queue.enqueue("C");
        queue.print();

        System.out.println("Front: " + queue.front());
        System.out.println("Dequeue: " + queue.dequeue());
        queue.print();

        System.out.println("Is queue empty? " + queue.isEmpty());
    }
}
