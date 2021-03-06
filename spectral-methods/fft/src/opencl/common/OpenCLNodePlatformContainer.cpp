//#define __CL_ENABLE_EXCEPTIONS
//#ifdef __APPLE__
//#include <OpenCL/cl.hpp>
//#else
//#include <CL/cl.hpp>
//#endif
#if defined(__cplusplus)
#define __CL_ENABLE_EXCEPTIONS
#include "cl.hpp"
#endif /* __cplusplus */

#include "OpenCLNodePlatformContainer.h"
#include "support.h"
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <assert.h>

using namespace std;
using namespace SHOC;

const int SHOC::OpenCLNodePlatformContainer::MAGIC_KEY_OPENCL_NODE_CONTAINER = 0x3178af13;

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::OpenCLNodePlatformContainer
//
// Purpose: 
//   Constructor. Creates a new OpenCL node container that is either 
//   initialized with platform data or left empty.
//
// Arguments:
//   do_initialize : specifies if the container should be instantiated with
//       platform data.
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
OpenCLNodePlatformContainer::OpenCLNodePlatformContainer (bool do_initialize) : 
           NodePlatformContainer<OpenCLPlatform>()
{
    // Platform
    if (do_initialize)
        initialize();
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::initialize
//
// Purpose: 
//   Initializes the container with platform information. 
//
// Arguments:
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
void 
OpenCLNodePlatformContainer::initialize ()
{
    cl_int err;
    vector<cl::Platform> clPlatforms;

    err = cl::Platform::get( &clPlatforms );
    CL_CHECK_ERROR(err);

    for( vector<cl::Platform>::iterator iter = clPlatforms.begin();
        iter != clPlatforms.end();
        iter++ )
    {
        OpenCLPlatform *openclPlatform = new OpenCLPlatform (*iter);
        platforms.push_back( openclPlatform );
        platformCount += 1;
    }
}


// ****************************************************************************
// Method: OpenCLNodePlatformContainer::OpenCLNodePlatformContainer
//
// Purpose: 
//   Copy constructor. Creates a new container that is an exact copy of
//   the container specified as a parameter.
//
// Arguments:
//   ondc: the OpenCL node platform container to be copied
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
OpenCLNodePlatformContainer::OpenCLNodePlatformContainer (const OpenCLNodePlatformContainer &ondc) :
             NodePlatformContainer<OpenCLPlatform> (ondc)
{
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::operator=
//
// Purpose: 
//   Copy operator. Copies the content of the specified container into
//   this container.
//
// Arguments:
//   ondc: the OpenCL node platform container to be copied
//
// Returns: 
//   a reference to this container
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
OpenCLNodePlatformContainer& 
OpenCLNodePlatformContainer::operator= (const OpenCLNodePlatformContainer &ondc)
{
    this->NodePlatformContainer<OpenCLPlatform>::operator= (ondc);
    return (*this);
}


// ****************************************************************************
// Method: OpenCLNodePlatformContainer::Print
//
// Purpose: 
//   Pretty print the content of the container.
//
// Arguments:
//   os: the output stream where the writing is done
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
void
OpenCLNodePlatformContainer::Print (ostream &os) const
{
    NodePlatformContainer<OpenCLPlatform>::Print (os);
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::writeObject
//
// Purpose: 
//   Implements the serialization method of the SerializableObject 
//   abstract class.
//
// Arguments:
//   oss: an output string stream where the serialized content is written
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
void 
OpenCLNodePlatformContainer::writeObject(ostringstream &oss) const
{
    oss << " " << MAGIC_KEY_OPENCL_NODE_CONTAINER << "\n";
    NodePlatformContainer<OpenCLPlatform>::writeObject (oss);
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::readObject
//
// Purpose: 
//   Implements the unserialization method of the SerializableObject 
//   abstract class.
//
// Arguments:
//   iss: the input string stream from where the serialized content is read
//
// Returns: 
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
void 
OpenCLNodePlatformContainer::readObject(istringstream &iss)
{
    int receivedKey = 0;
    
    iss >> receivedKey;
    if (receivedKey != MAGIC_KEY_OPENCL_NODE_CONTAINER)  // wrong magic key
    {
        cerr << "Wrong magic key received " << receivedKey 
             << " while unserializing an OpenCLNodePlatformContainer object." << endl;
        exit (-2);
    }
    NodePlatformContainer<OpenCLPlatform>::readObject (iss);
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::operator<
//
// Purpose: 
//   Less operator: compares two OpenCL node container objects based on
//   an assumed ordering.
//
// Arguments:
//   ndc: the OpenCL node container object to be compared against 
//   this instance.
//
// Returns: true - if this container precedes the specified container
//          false - otherwise
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
bool 
OpenCLNodePlatformContainer::operator< (const OpenCLNodePlatformContainer &ndc) const
{
    return (NodePlatformContainer<OpenCLPlatform>::operator< (ndc));
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::operator>
//
// Purpose: 
//   Greater operator: compares two OpenCL node container objects based on
//   an assumed ordering.
//
// Arguments:
//   ndc: the OpenCL node container object to be compared against 
//   this instance.
//
// Returns: true - if this container succeeds the specified container
//          false - otherwise
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
bool 
OpenCLNodePlatformContainer::operator> (const OpenCLNodePlatformContainer &ndc) const
{
    return (NodePlatformContainer<OpenCLPlatform>::operator> (ndc));
}

// ****************************************************************************
// Method: OpenCLNodePlatformContainer::operator==
//
// Purpose: 
//   Equality operator: compares two OpenCL node container objects based on
//   an assumed ordering.
//
// Arguments:
//   ndc: the OpenCL node container object to be compared against 
//   this instance.
//
// Returns: true - if this container and the specified container are equal
//          false - otherwise
//
// Note: 
//
// Programmer: Gabriel Marin
// Creation: September 22, 2009
//
// Modifications:
//
// ****************************************************************************
bool 
OpenCLNodePlatformContainer::operator== (const OpenCLNodePlatformContainer &ndc) const
{
    return (NodePlatformContainer<OpenCLPlatform>::operator== (ndc));
}
