package com.mycompany.asst_2;

/*
Create a Java class, RecentFileCache, that simulates an application's "Recent Files" list. 
The list must maintain the order of access, where the Head of the linked list is the Most Recently Used (MRU) file, 
and the Tail is the Least Recently Used (LRU) file. The cache has a fixed maximum capacity.

Core Requirements:
>> Doubly Linked List : Implement a Doubly Linked List with a private inner class Node that stores the file name 
and pointers to the prev and next nodes.
>> LRU Logic -> accessFile method: This is the main operation. It must handle three scenarios efficiently:
 - File Found: If the file is already in the cache, move its corresponding node to the Head of the list.
 - File Not Found & Capacity Available: Add a new node for the file to the Head of the list.
 - File Not Found & Full Capacity: First, remove the node at the Tail (the LRU element). 
   Then, add the new file to the Head of the list.
note that maximum capacity must be specified, so let it be 10.
*/
public class RecentFileCache {
    Node head;
    Node tail;
    int size;
    
    void accessFile(String filename) {
        Node file = linearSearch(filename);
        if(file != null) { // found
            remove(file);
            insertFirst(file);
        }
        else if(file == null && size < 10) { // not found and available
            insertFirst(new Node(filename));
            size++;
        }
        else { // not found and not available
            remove(tail);
            insertFirst(new Node(filename));
        }
    }
    
    void insertFirst(Node file) {
        if(head == null && tail == null) { // empty list
            head = file;
            tail = file;
            file.prev = null;
            file.next = null;
            return;
        }
        
       file.next = head;
       file.prev = null;
       head.prev = file;
       head = file;
    }
    
    void remove(Node file) {
        if(file.prev == null) { // first element
            head = file.next;
        } else {
            file.prev.next = file.next;
        }
        
        if(file.next == null) { // last element
            tail = file.prev;
        } else {
            file.next.prev = file.prev;
        }
    }
    
    Node linearSearch(String filename) {
        Node temp = head;
        while(temp != null) {
            if(temp.filename.equalsIgnoreCase(filename)) {
                break;
            }
            temp = temp.next;
        }
        return temp;
    }
    
    private class Node {
        String filename;
        Node next;
        Node prev;
        public Node(String filename) {
            this.filename = filename;
        }
    }
    
   @Override
    public String toString() {
        if (head == null) {
            return "[]";
        }
        Node temp = head;
        StringBuilder s = new StringBuilder("[");
        while (temp != null) {
            s.append(temp.filename);
            if (temp.next != null) s.append(", ");
            temp = temp.next;
        }
        s.append("]");
        return s.toString();
    }
}
