package com.mycompany.asst_1;

public class Student {
    String fname;
    String lname;
    int id;

    public Student(String fname, String lname) {
        this.fname = fname;
        this.lname = lname;
        this.id = this.hashCode();
    }

    @Override
    public String toString() {
        return "Student{" + "fname=" + fname + ", lname=" + lname + ", id=" + id + '}';
    }
    
    
}
