//
// ex: set ro:
// DO NOT EDIT.
// generated by smc (http://smc.sourceforge.net/)
// from file : recognizer.sm
//

#ifndef RECOGNIZER_SM_H
#define RECOGNIZER_SM_H


#define SMC_USES_IOSTREAMS

#include <statemap.h>

// Forward declarations.
class MainMap;
class MainMap_Preambula;
class MainMap_Username;
class MainMap_Server;
class MainMap_Domain;
class MainMap_Zone;
class MainMap_Error;
class MainMap_End;
class MainMap_Default;
class RecognizerState;
class recognizerContext;
class Recognizer;

class RecognizerState :
    public statemap::State
{
public:

    RecognizerState(const char * const name, const int stateId)
    : statemap::State(name, stateId)
    {};

    virtual void Entry(recognizerContext&) {};
    virtual void Exit(recognizerContext&) {};

    virtual void nil(recognizerContext& context);
    virtual void readChar(recognizerContext& context);

protected:

    virtual void Default(recognizerContext& context);
};

class MainMap
{
public:

    static MainMap_Preambula Preambula;
    static MainMap_Username Username;
    static MainMap_Server Server;
    static MainMap_Domain Domain;
    static MainMap_Zone Zone;
    static MainMap_Error Error;
    static MainMap_End End;
};

class MainMap_Default :
    public RecognizerState
{
public:

    MainMap_Default(const char * const name, const int stateId)
    : RecognizerState(name, stateId)
    {};

};

class MainMap_Preambula :
    public MainMap_Default
{
public:
    MainMap_Preambula(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void readChar(recognizerContext& context);
};

class MainMap_Username :
    public MainMap_Default
{
public:
    MainMap_Username(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void readChar(recognizerContext& context);
};

class MainMap_Server :
    public MainMap_Default
{
public:
    MainMap_Server(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void readChar(recognizerContext& context);
};

class MainMap_Domain :
    public MainMap_Default
{
public:
    MainMap_Domain(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void readChar(recognizerContext& context);
};

class MainMap_Zone :
    public MainMap_Default
{
public:
    MainMap_Zone(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void readChar(recognizerContext& context);
};

class MainMap_Error :
    public MainMap_Default
{
public:
    MainMap_Error(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void nil(recognizerContext& context);
};

class MainMap_End :
    public MainMap_Default
{
public:
    MainMap_End(const char * const name, const int stateId)
    : MainMap_Default(name, stateId)
    {};

    virtual void nil(recognizerContext& context);
};

class recognizerContext :
    public statemap::FSMContext
{
public:

    explicit recognizerContext(Recognizer& owner)
    : FSMContext(MainMap::Preambula),
      _owner(&owner)
    {};

    recognizerContext(Recognizer& owner, const statemap::State& state)
    : FSMContext(state),
      _owner(&owner)
    {};

    virtual void enterStartState()
    {
        getState().Entry(*this);
    }

    inline Recognizer& getOwner()
    {
        return *_owner;
    };

    inline RecognizerState& getState()
    {
        if (_state == NULL)
        {
            throw statemap::StateUndefinedException();
        }

        return dynamic_cast<RecognizerState&>(*_state);
    };

    inline void nil()
    {
        getState().nil(*this);
    };

    inline void readChar()
    {
        getState().readChar(*this);
    };

private:

    Recognizer* _owner;
};


#endif // RECOGNIZER_SM_H

//
// Local variables:
//  buffer-read-only: t
// End:
//
