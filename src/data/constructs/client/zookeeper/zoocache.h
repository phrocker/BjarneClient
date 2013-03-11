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

#ifndef ZOOCACHE_H
#define ZOOCACHE_H

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <initializer_list>
#include "../../inputvalidation.h"
#include <zookeeper/zookeeper.hh>
#include "zookeepers.h"
#include "watch.h"

using namespace org::apache::zookeeper;
using namespace std;

#include <time.h>
#include <pthread.h>

namespace cclient {
namespace data {
namespace zookeeper {

class ZooCache: protected GetCallback, protected GetChildrenCallback {
public:
	ZooCache(string zks, int timeout, Watch *watcher) {
		zk = ZooKeepers::getSession(zks, timeout, NULL);
		dataCache = new map<string, string>();
		childCache = new map<string, vector<string>>();
	}

	auto getChildren(const string path) {

		boost::shared_ptr<Watch> watchers(watcher);

		boost::shared_ptr<GetCallback> callBack(this);

		zk->getChildren(path, watchers, callBack);

		return callBackCondition(path, childCache);
	}

	auto getPath(const string path) {
		boost::shared_ptr<Watch> watchers(watcher);

		boost::shared_ptr<GetCallback> callBack(this);

		zk->get(path, watchers, callBack);

		return callBackCondition(path, dataCache);
	}

	auto getLockData(const string path) {
		vector<string> children = getChildren(path);
		if (IsEmpty(&children)) {
			return NULL;
		}

			std::sort(children.begin(),children.end());

				string lockNode = children.at(0);

				string lockPath = path;

				lockPath.append("/");

				lockPath.append(lockNode);

				return getPath(lockPath);

			}

		private:

			auto callBackCondition(string waitPath, auto *cache) {
				do {
					pthread_cond_wait(&cacheUpdate, &cacheLock);
				} while (cache->find(waitPath) == cache->end());

				return cache->find(waitPath);
			}

			void process(ReturnCode::type rc, const std::string &path,
					const std::string &data, const data::Stat & stat) {
				dataCache->insert(path, data);
				pthread_cond_broadcast(&cacheUpdate);
			}

			void process(ReturnCode::type rc, const std::string& path,
					const std::vector<std::string>& children,
					const data::Stat& stat) {
				childCache->insert(path, children);
				pthread_cond_broadcast(&cacheUpdate);
			}

			pthead_mutex_t cacheLock = PTHREAD_MUTEX_INITIALIZER;
			pthread_cond_t cacheUpdate = PTHREAD_COND_INITIALIZER;

			auto *childCache;

			auto *dataCache;

			auto *l;

			ZooKeeper *zk;
			Watch *watcher;

		};

		}
		}
		}
#endif // ZOOCACHE\_H
