/*
 * This file is part of CcCompare.
 *
 * CcCompare is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CcCompare is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with CcCompare.  If not, see <http://www.gnu.org/licenses/>.
 **/
/**
 * @page      CcCompare
 * @copyright Andreas Dirmeier (C) 2017
 * @author    Andreas Dirmeier
 * @par       Web: http://coolcow.de
 * @version   0.01
 * @date      2016-04
 * @par       Language   C++ ANSI V3
 * @brief     Class CcCompare
 **/
#ifndef CcCompare_H_
#define CcCompare_H_

#include "CcBase.h"
#include "CcUserList.h"
#include "CcApp.h"
#include "CcArguments.h"

/**
 * @brief Class impelmentation
 */
class CcCompare : public CcApp
{
public:
  /**
   * @brief Constructor
   */
  CcCompare(void) {}
  /**
   * @brief Constructor with Arguments
   */
  CcCompare( const CcArguments& oArguments ) : m_oArguments(oArguments) {}

  /**
   * @brief CopyConstructor
   */
  CcCompare( const CcCompare& oToCopy );

  /**
   * @brief MoveConstructor
   */
  CcCompare( CcCompare&& oToMove );

  /**
   * @brief Destructor
   */
  virtual ~CcCompare( void );


  CcCompare& operator=(const CcCompare& oToCopy);
  CcCompare& operator=(CcCompare&& oToMove);

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

#endif /* CcCompare_H_ */
