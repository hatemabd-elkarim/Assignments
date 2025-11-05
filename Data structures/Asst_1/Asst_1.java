package com.mycompany.asst_1;

public class Asst_1 {

    public static void main(String[] args) {
        LinearArray arr = new LinearArray(20);
        System.out.println(arr.arr.length); //20
        LinearArray arr1 = new LinearArray();
        System.out.println(arr1.arr.length); // 10
        
        System.out.println(arr.size);
        arr.insertFirst(10);
        arr.insertFirst(20);
        arr.insertFirst(30);        
        arr.insertFirst(40);        
        arr.insertFirst(50);
        arr.insertLast(0);
        System.out.println(arr.size); // 6
        System.out.println(arr); // [50,40,30,20,10,0]
        
        System.out.println(arr.linearSearch(60));
        System.out.println(arr.linearSearch(50)); // 0
        System.out.println(arr.linearSearch(40)); // 1
        System.out.println(arr.linearSearch(0)); // 5
        
        arr.delete(50);
        arr.delete(0);
        arr.delete(30);
        System.out.println(arr.size); // 3
        System.out.println(arr); // [40,20,10]
        
        System.out.println("");
        
        LinearArrayStudents arrSt = new LinearArrayStudents(20); // -1
        System.out.println(arrSt.arr.length); //20
        LinearArrayStudents arrSt1 = new LinearArrayStudents();
        System.out.println(arrSt1.arr.length); // 10
        
        Student s0 = new Student("Mahmoud", "FathAllah");
        Student s1 = new Student("Abdallh", "Ashrah");
        Student s2 = new Student("Hatem", "Ayman");
        Student s3 = new Student("Ahmed", "Othman");
        
        System.out.println(arr.size);
        arrSt.insertFirst(s0);
        arrSt.insertFirst(s1);
        arrSt.insertFirst(s2);
        arrSt.insertLast(s3);
        System.out.println(arrSt.size); // 4
        System.out.println(arrSt); // [Hatem Ayman, Abdallh Ashrah, Mahmoud FathAllah, Ahmed Othman]
        
        System.out.println(arrSt.linearSearch(123)); // -1
        System.out.println(arrSt.linearSearch(s0.id)); // 2
        System.out.println(arrSt.linearSearch(s1.id)); // 1
        System.out.println(arrSt.linearSearch(s3.id)); // 3
        
        
        arrSt.delete(s3.id);
        System.out.println(arrSt.size); // 3
        System.out.println(arrSt); // [Hatem Ayman, Abdallh Ashrah, Mahmoud FathAllah]   
    }
}
