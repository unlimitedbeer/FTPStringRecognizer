//
// ex: set ro:
// DO NOT EDIT.
// generated by smc (http://smc.sourceforge.net/)
// from file : recognizer.sm
//


// Initial revision
//


#include "stdafx.h"

using namespace statemap;

// Static class declarations.
MainMap_Preambula MainMap::Preambula("MainMap::Preambula", 0);
MainMap_Username MainMap::Username("MainMap::Username", 1);
MainMap_Server MainMap::Server("MainMap::Server", 2);
MainMap_Domain MainMap::Domain("MainMap::Domain", 3);
MainMap_Zone MainMap::Zone("MainMap::Zone", 4);
MainMap_Error MainMap::Error("MainMap::Error", 5);
MainMap_End MainMap::End("MainMap::End", 6);

void RecognizerState::nil(recognizerContext& context)
{
    Default(context);
}

void RecognizerState::readChar(recognizerContext& context, const char c)
{
    Default(context);
}

void RecognizerState::Default(recognizerContext& context)
{
    throw (
        TransitionUndefinedException(
            context.getState().getName(),
            context.getTransition()));

}

void MainMap_Preambula::readChar(recognizerContext& context, const char c)
{
    Recognizer& ctxt = context.getOwner();

    if (ctxt.isPreambulaFinished(c))
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.preambulaPassed(c);
            context.setState(MainMap::Username);
        }
        catch (...)
        {
            context.setState(MainMap::Username);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isPreambulaCorrect(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.preambulaReading(c);
            context.setState(MainMap::Preambula);
        }
        catch (...)
        {
            context.setState(MainMap::Preambula);
            throw;
        }
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.showError(c);
            context.setState(MainMap::Error);
        }
        catch (...)
        {
            context.setState(MainMap::Error);
            throw;
        }
        context.getState().Entry(context);
    }

}

void MainMap_Username::readChar(recognizerContext& context, const char c)
{
    Recognizer& ctxt = context.getOwner();

    if (ctxt.isUsernameFinished(c))
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.usernamePassed(c);
            context.setState(MainMap::Server);
        }
        catch (...)
        {
            context.setState(MainMap::Server);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isUsernameCorrect(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.usernameReading(c);
            context.setState(MainMap::Username);
        }
        catch (...)
        {
            context.setState(MainMap::Username);
            throw;
        }
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.showError(c);
            context.setState(MainMap::Error);
        }
        catch (...)
        {
            context.setState(MainMap::Error);
            throw;
        }
        context.getState().Entry(context);
    }

}

void MainMap_Server::readChar(recognizerContext& context, const char c)
{
    Recognizer& ctxt = context.getOwner();

    if (ctxt.isServerFinished(c))
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.serverPassed(c);
            context.setState(MainMap::Domain);
        }
        catch (...)
        {
            context.setState(MainMap::Domain);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isServerCorrect(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.serverReading(c);
            context.setState(MainMap::Server);
        }
        catch (...)
        {
            context.setState(MainMap::Server);
            throw;
        }
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.showError(c);
            context.setState(MainMap::Error);
        }
        catch (...)
        {
            context.setState(MainMap::Error);
            throw;
        }
        context.getState().Entry(context);
    }

}

void MainMap_Domain::readChar(recognizerContext& context, const char c)
{
    Recognizer& ctxt = context.getOwner();

    if (ctxt.isDomainFinished(c))
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.domainPassed(c);
            context.setState(MainMap::Zone);
        }
        catch (...)
        {
            context.setState(MainMap::Zone);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isStringFinished(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.domainPassed(c);
            context.setState(MainMap::End);
        }
        catch (...)
        {
            context.setState(MainMap::End);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isDomainCorrect(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.domainReading(c);
            context.setState(MainMap::Domain);
        }
        catch (...)
        {
            context.setState(MainMap::Domain);
            throw;
        }
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.showError(c);
            context.setState(MainMap::Error);
        }
        catch (...)
        {
            context.setState(MainMap::Error);
            throw;
        }
        context.getState().Entry(context);
    }

}

void MainMap_Zone::readChar(recognizerContext& context, const char c)
{
    Recognizer& ctxt = context.getOwner();

    if (ctxt.isZoneFinished(c))
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.zonePassed(c);
            context.setState(MainMap::End);
        }
        catch (...)
        {
            context.setState(MainMap::End);
            throw;
        }
        context.getState().Entry(context);
    }
    else if (ctxt.isZoneCorrect(c))

    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.zoneReading(c);
            context.setState(MainMap::Zone);
        }
        catch (...)
        {
            context.setState(MainMap::Zone);
            throw;
        }
        context.getState().Entry(context);
    }
    else
    {
        context.getState().Exit(context);
        context.clearState();
        try
        {
            ctxt.showError(c);
            context.setState(MainMap::Error);
        }
        catch (...)
        {
            context.setState(MainMap::Error);
            throw;
        }
        context.getState().Entry(context);
    }

}

void MainMap_Error::nil(recognizerContext& context)
{


}

void MainMap_End::nil(recognizerContext& context)
{


}

//
// Local variables:
//  buffer-read-only: t
// End:
//
