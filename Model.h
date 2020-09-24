#pragma once

class Model {
    public:
        //bool exitFunc();
        void setExitFunc( bool (*someFunc)() );
        void Start();
    private:
        bool isRunning;
        bool exitFunc;
};