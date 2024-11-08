#ifndef ENGINE_HEADER
#define ENGINE_HEADER

class Engine
{
public:
    Engine();
    ~Engine();
    int Run();

protected:
    virtual void Initialize() = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void Draw() = 0;

private:

};

#endif