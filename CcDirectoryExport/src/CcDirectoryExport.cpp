/*
* This file is part of CcDirectoryExport.
*
* CcDirectoryExport is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CcDirectoryExport is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with CcDirectoryExport.  If not, see <http://www.gnu.org/licenses/>.
**/
/**
* @file
* @copyright Andreas Dirmeier (C) 2017
* @author    Andreas Dirmeier
* @par       Web: http://coolcow.de
* @version   0.01
* @date      2016-04
* @par       Language   C++ ANSI V3
* @brief     Implemtation of class CcDirectoryExport
*/
#include "CcKernel.h"
#include "CcDirectory.h"
#include "CcDirectoryExport.h"
#include "CcFile.h"
#include "CcConsole.h"
#include "CcError.h"

CcDirectoryExport::CcDirectoryExport(const CcDirectoryExport& oToCopy)
{
  operator=(oToCopy);
}

CcDirectoryExport::CcDirectoryExport(CcDirectoryExport&& oToMove)
{
  operator=(std::move(oToMove));
}

CcDirectoryExport::~CcDirectoryExport(void)
{
}

void CcDirectoryExport::run()
{
  if (m_oArguments.size() == 4)
  {
    m_sSource   = m_oArguments[1];
    m_sModified = m_oArguments[2];
    m_sOutput   = m_oArguments[3];
    m_sSource.normalizePath();
    m_sModified.normalizePath();
    m_sOutput.normalizePath();
    if (CcDirectory::exists(m_sSource) &&
        CcDirectory::exists(m_sModified) &&
        (CcDirectory::exists(m_sOutput) || CcDirectory::create(m_sOutput, true)))
    {
      CcConsole::writeLine("Start comparing with following settings:");
      CcConsole::writeLine(" - Source:   " + m_sSource);
      CcConsole::writeLine(" - Modified: " + m_sModified);
      CcConsole::writeLine(" - Output:   " + m_sOutput);
      CcConsole::writeLine("First, clean Directory: (protected files must be deleted manually)");
      CcDirectory::clear(m_sOutput, true);
      CcConsole::writeLine("Start Merging");
      compareDirectories("");
    }
    else
    {
      CcConsole::writeLine("At least one directory not existing");
      setExitCode(EError::FSDirNotFound);
    }
  }
  else
  {
    CcConsole::writeLine("Wrong number of Paramters, 3 are required");
    CcConsole::writeLine("  [Source] [Modified] [Output]");
    setExitCode(EError::CommandRequiredParameter);
  }
}

void CcDirectoryExport::compareDirectories(const CcString& sSource)
{
  CcString sCompareSource = m_sSource;
  CcString sCompareModified = m_sModified;
  sCompareSource.appendPath(sSource);
  sCompareModified.appendPath(sSource);
  CcFileInfoList oSourceList = CcDirectory::getFileList(sCompareSource);
  CcFileInfoList oModifiedList = CcDirectory::getFileList(sCompareModified);
  for (const CcFileInfo& oSource : oSourceList)
  {
    bool bModifiedExists = oModifiedList.containsFile(oSource.getName());
    if (bModifiedExists)
    {
      const CcFileInfo& oModified = oModifiedList.getFile(oSource.getName());
      if (oSource.isFile() && oModified.isFile())
      {
        CcString sFilePathSource = m_sSource;
        CcString sFilePathModified = m_sModified;
        sFilePathSource.appendPath(sSource);
        sFilePathModified.appendPath(sSource);
        sFilePathSource.appendPath(oSource.getName());
        sFilePathModified.appendPath(oSource.getName());
        if (!CcFile::compare(sFilePathSource, sFilePathModified, true))
        {
          copyModified(sSource, oSource.getName());
        }
      }
      else if (oSource.isDir() && oModified.isDir())
      {
        CcString sNextSource = sSource;
        sNextSource.appendPath(oSource.getName());
        compareDirectories(sNextSource);
      }
      else
      {
        copyModified(sSource, oSource.getName());
      }
      oModifiedList.removeFile(oSource.getName());
    }
    else
    {
      copyDeleted(sSource, oSource.getName());
    }
  }
  for (const CcFileInfo& oModified : oModifiedList)
  {
    copyNew(sSource, oModified.getName());
  }
}

bool CcDirectoryExport::copyNew(const CcString& sPath, const CcString& sFileName)
{
  bool bRet = false;
  CcString sFilePathFrom = m_sModified;
  sFilePathFrom.appendPath(sPath);
  CcString sFilePathTo = m_sOutput;
  sFilePathTo.appendPath("new");
  sFilePathTo.appendPath(sPath);
  if (CcDirectory::exists(sFilePathTo) ||
      CcDirectory::create(sFilePathTo, true))
  {
    sFilePathFrom.appendPath(sFileName);
    sFilePathTo.appendPath(sFileName);
    bRet = CcFile::copy(sFilePathFrom, sFilePathTo);
  }
  return bRet;
}

bool CcDirectoryExport::copyModified(const CcString& sPath, const CcString& sFileName)
{
  bool bRet = false;
  CcString sFilePathFrom = m_sModified;
  sFilePathFrom.appendPath(sPath);
  CcString sFilePathTo = m_sOutput;
  sFilePathTo.appendPath("modified");
  sFilePathTo.appendPath(sPath);
  if (CcDirectory::exists(sFilePathTo) ||
    CcDirectory::create(sFilePathTo, true))
  {
    sFilePathFrom.appendPath(sFileName);
    sFilePathTo.appendPath(sFileName);
    bRet = CcFile::copy(sFilePathFrom, sFilePathTo);
  }
  return bRet;
}

bool CcDirectoryExport::copyDeleted(const CcString& sPath, const CcString& sFileName)
{
  bool bRet = false;
  CcString sFilePathFrom = m_sSource;
  sFilePathFrom.appendPath(sPath);
  CcString sFilePathTo = m_sOutput;
  sFilePathTo.appendPath("deleted");
  sFilePathTo.appendPath(sPath);
  if (CcDirectory::exists(sFilePathTo) ||
    CcDirectory::create(sFilePathTo, true))
  {
    sFilePathFrom.appendPath(sFileName);
    sFilePathTo.appendPath(sFileName);
    bRet = CcFile::copy(sFilePathFrom, sFilePathTo);
  }
  return bRet;
}


CcDirectoryExport& CcDirectoryExport::operator=(const CcDirectoryExport& oToCopy)
{
  CCUNUSED(oToCopy);
  return *this;
}

CcDirectoryExport& CcDirectoryExport::operator=(CcDirectoryExport&& oToMove)
{
  if (this != &oToMove)
  {
  }
  return *this;
}
