#ifndef DATASTRUCTURE_RECORD_H
#define DATASTRUCTURE_RECORD_H

#define KEY_SIZE 64
#define VALUE_SIZE 64

class Record {
private:
    char key[KEY_SIZE];
    char value[VALUE_SIZE];
public:
    Record(char *k = "", char *v = "") { set(k, v); }

    void set(char *k, char *v = "");

    void reset() { set("", ""); }

    bool isEmpty() { return key[0] == '\0'; }

    bool equal(char *k);

    void display();

};


#endif //DATASTRUCTURE_RECORD_H
