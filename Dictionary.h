//
//  Dictionary.h
//  abstract-data-type
//
//  Created by 袁麓 on 2019/2/24.
//  Copyright © 2019 袁麓. All rights reserved.
//

#ifndef Dictionary_h
#define Dictionary_h

template <typename K, typename V> struct Dictionary {
    virtual int size() const = 0;// 当前词条总数
    virtual bool put(K, V) = 0;// 插入词条
    virtual V* get(K k) = 0;// 读取词条
    virtual bool remove(K k) = 0;// 删除词条
};

#endif /* Dictionary_h */
