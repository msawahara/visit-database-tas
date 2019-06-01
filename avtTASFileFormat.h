  /*****************************************************************************
*
* Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/


// ************************************************************************* //
//                            avtTASFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_TAS_FILE_FORMAT_H
#define AVT_TAS_FILE_FORMAT_H

#include <avtSTSDFileFormat.h>


// ****************************************************************************
//  Class: avtTASFileFormat
//
//  Purpose:
//      Reads in TAS files as a plugin to VisIt.
//
//  Programmer: sawahara -- generated by xml2avt
//  Creation:   Fri May 31 01:25:32 PDT 2019
//
// ****************************************************************************

class avtTASFileFormat : public avtSTSDFileFormat
{
  public:
                       avtTASFileFormat(const char *filename);
    virtual           ~avtTASFileFormat();

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, const char *type,
    //                                  void *args, DestructorFunction &);
    //

    //
    // These are used to declare what the current time and cycle are for the
    // file.  These should only be defined if the file format knows what the
    // time and/or cycle is.
    //
    // virtual int       GetCycle(void);
    // virtual double    GetTime(void);
    //

    virtual const char    *GetType(void)   { return "TAS"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(const char *);
    virtual vtkDataArray  *GetVar(const char *);
    virtual vtkDataArray  *GetVectorVar(const char *);

  protected:
    // DATA MEMBERS
    enum EGridType {
		  GRID_UNV,
		  GRID_UNV2
	  };
    EGridType gridType;
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);
    std::string            gridFilename, rsltFilename;
    size_t                 n_node, n_tetra, n_edge, n_tri, n_pri, n_pyr, n_quad, n_hex;
  
  private:
    class dimdatReader {
      public:
          dimdatReader(const char *filename);
         ~dimdatReader();

        const std::string getGname(void);
        const std::string getCname(void);
        const int getZones(void);

      private:
        typedef struct DIMDATData_t {
          std::string gname, cname;
          size_t zones;
        } DIMDATData;
        DIMDATData dimdat;
    };
    class unformattedReader {
      public:
          unformattedReader(const char *filename);
         ~unformattedReader();

        void setSwapEndian(bool enableSwap);
        size_t getRecordLength(void);

        int readInt32(int32_t *dest, size_t length);
        int readDouble(double *dest, size_t length);
        int skip(size_t length);

      private:
        typedef int32_t RecordLength_t;
        std::ifstream     ifsGrid, ifsRslt;
        bool swap = false;
        int32_t swapInt32(int32_t value);
        double swapDouble(double value);
    };

    dimdatReader *dimdat;
};
#endif
