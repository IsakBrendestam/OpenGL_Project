#ifndef ENGINE_HEADER
#define ENGINE_HEADER

class Engine
{
public:
    Engine();
    ~Engine();
    int Run();

protected:
    virtual void Update(double deltaTime);

private:

};

#endif