package com.mycompany.asst_2;

public class Asst_2 {

    public static void main(String[] args) {
        RecentFileCache rf = new RecentFileCache();
        rf.accessFile("test.txt");
        rf.accessFile("test1.txt");
        rf.accessFile("test.txt");
        rf.accessFile("test.txt");
        rf.accessFile("test2.txt");
        rf.accessFile("test3.txt");
        rf.accessFile("test4.txt");
        rf.accessFile("test5.txt");
        rf.accessFile("test6.txt");
        rf.accessFile("test7.txt");
        rf.accessFile("test8.txt");
        rf.accessFile("test9.txt");
        rf.accessFile("test.txt");
        rf.accessFile("test10.txt");
        rf.accessFile("test11.txt");
        System.out.println(rf);
    }
}
