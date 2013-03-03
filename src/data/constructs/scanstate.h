/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SCANSTATE_H
#define SCANSTATE_H

#include <iostream>
#include <map>

#include <vector>

using namespace std;
#include "inputvalidation.h"
#include "Range.h"
#include "security/AuthInfo.h"
#include "security/Authorizations.h"
#include "../client/TabletLocation.h"
#include "column.h"
#include "../../data_types.h"
#include "../exceptions/ClientException.h"

namespace cclient {
namespace data {

    using namespace cclient::data::security;
    using namespace cclient::exceptions;
   using namespace accumulo::data;


class ScanState
{

public:
ScanState();
ScanState(AuthInfo *credentials, string tablename, Authorizations *auths, Range *range, set<Column*> *fetchedColumns, uint64_t size,
	  vector<IterInfo*> *iters, map<string,map<string,string> *options, bool isolated) : isolated(isolated), tableName(tablename), credentials(credentials),auths(auths), skipStartRow(false),size(size)
{
  if (IsEmpty(credentials) || IsEmpty(tablename) || IsEmpty(auths) )
  {
    throw ClientException("Credentials, tablename, and authorizations cannot be null");
  }
  
  
  if (!IsEmpty(fetchedColumns))
    columns.insert(fetchedColumns->begin(),fetchedColumns->end());
  
  if (!IsEmpty(iters))
    serverSideIteratorList.insert(iters->begin(),iters->end());
  
  if (!IsEmpty(options))
    serverSideOptions.insert( options->begin(), options->end() );
  
    Key *startKey = range->getStartKey();
  
    if (IsEmpty(startKey))
    {	
      startKey = new Key();
    }
    
    std::pair<char*,size_t> row = startKey->getRow();
    startRow = string(row.first,row.second);
    
  
  
}
ScanState(const ScanState& other);
virtual ~ScanState();
virtual ScanState& operator=(const ScanState& other);
virtual bool operator==(const ScanState& other) const;

   bool isIsolated() const { return isolated; }
   
   string getTableName() const { return tableName; }
   
   string getStartRow() const { return startRow; }
   
   Range *getRange() const { return myRange; }
   
   uint64_t getSize()  const { return size; }
   
   AuthInfo *getCredentials()  const { return credentials; }
   
   Authorizations *getAuths()  const { return auths; }
   
   TabletLocation *getPrevious() const { return prevLoc; }
   
   uint64_t getScanId() const { return scanId; }
   
   bool isFinished(){ return finished; }
   
   bool setFinished(bool fin = true){ finished = fin; }
   
   auto getIteratorList() const { return &serverSideIteratorList; }
   
   auto getOptions() const { return &serverSideOptions; }
   

protected:
    bool isolated;
    string tableName;
    string startRow;
    bool skipStartRow;
    Range *myRange;
    
    uint64_t size;
    
    AuthInfo *credentials;
    
    Authorizations *auths;
    
    vector<Column*> columns;
    
    TabletLocation *prevLoc;
    
    uint64_t scanId;
    
    bool finished;
    
    vector<IterInfo*> serverSideIteratorList;
    
    map<string,map<string,string> serverSideOptions;
    
    
    
};

}}
#endif // SCANSTATE_H
