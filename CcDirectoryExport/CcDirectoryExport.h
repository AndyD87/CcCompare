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
 * @page      CcDirectoryExport
 * @copyright Andreas Dirmeier (C) 2017
 * @author    Andreas Dirmeier
 * @par       Web: http://coolcow.de
 * @version   0.01
 * @date      2016-04
 * @par       Language   C++ ANSI V3
 * @brief     Class CcDirectoryExport
 **/
#ifndef CcDirectoryExport_H_
#define CcDirectoryExport_H_

#include "CcBase.h"
#include "CcUserList.h"
#include "CcApp.h"
#include "CcArguments.h"

/**
 * @brief Class impelmentation
 */
class CcDirectoryExport : public CcApp
{
public:
  /**
   * @brief Constructor
   */
  CcDirectoryExport(void) {}
  /**
   * @brief Constructor with Arguments
   */
  CcDirectoryExport( const CcArguments& oArguments ) : m_oArguments(oArguments) {}

  /**
   * @brief CopyConstructor
   */
  CcDirectoryExport( const CcDirectoryExport& oToCopy );

  /**
   * @brief MoveConstructor
   */
  CcDirectoryExport( CcDirectoryExport&& oToMove );

  /**
   * @brief Destructor
   */
  virtual ~CcDirectoryExport( void );


  CcDirectoryExport& operator=(const CcDirectoryExport& oToCopy);
  CcDirectoryExport& operator=(CcDirectoryExport&& oToMove);

  void run() override;

  void compareDirectories(const CcString& sSource);

  bool copyNew(const CcString& sPath, const CcString& sFileName);
  bool copyModified(const CcString& sPath, const CcString& sFileName);
  bool copyDeleted(const CcString& sPath, const CcString& sFileName);
private:
  CcArguments m_oArguments;
  CcString m_sSource;
  CcString m_sModified;
  CcString m_sOutput;
};

#endif /* CcDirectoryExport_H_ */
