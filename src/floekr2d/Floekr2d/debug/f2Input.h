#include <iostream>
#define F2_MAX_INPUT 256

class f2Input
{
public:
    f2Input() :input(NULL), inputNumber(0) {}

    void initInput()
    {
        // 已分配内存
        if(input)
        {
            delete input;
            input = NULL;
        }

        input = new char[F2_MAX_INPUT];
        inputNumber = 0;
    }

    void addChar(unsigned char c)
    {
        input[inputNumber] = c;
        inputNumber = (inputNumber + 1) % F2_MAX_INPUT;
        input[inputNumber] = '\0';
    }

    void deleteChar()
    {
        if(inputNumber != 0)
            inputNumber = (inputNumber - 1) % F2_MAX_INPUT;

        input[inputNumber] = '\0';
    }

    void clear()
    {
        inputNumber = 0;
        memset(input, '\0', sizeof(input));
    }

    char* getInputChar()
    {
        //char* inputChar = new char[inputNumber];
        //strcpy(inputChar, input);
        return input;
    }

private:

    // 最多256字长命令
    int inputNumber;
    char* input;
};