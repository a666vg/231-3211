#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton;

class SingletonDestroyer
{
private:
    Singleton* p_instance;

public:
    ~SingletonDestroyer()
    {
        delete p_instance;
    }
    void init(Singleton* p)
    {
        p_instance = p;
    }
};

class Singleton
{
private:
    static Singleton* p_instance;
    static SingletonDestroyer destroyer;

protected:
    Singleton() {}
    Singleton(const Singleton&);
    ~Singleton() {}
    Singleton& operator=(Singleton&);
    friend class SingletonDestroyer;

public:
    static Singleton* getInstance()
    {
        if (!p_instance)
        {
            p_instance = new Singleton();
            destroyer.init(p_instance);
        }
        return p_instance;
    }
};

Singleton* p_instance;
SingletonDestroyer destroyer;

#endif // SINGLETON_H
