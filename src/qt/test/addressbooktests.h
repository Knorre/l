// Copyright (c) 2018-2019 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_QT_TEST_ADDRESSBOOKTESTS_H
#define DIGIBYTE_QT_TEST_ADDRESSBOOKTESTS_H

#include <QObject>
#include <QTest>

namespace interfaces {
class Node;
} // namespace interfaces

class AddressBookTests : public QObject
{
public:
    AddressBookTests(interfaces::Node& node) : m_node(node) {}
    interfaces::Node& m_node;

    Q_OBJECT

private Q_SLOTS:
    void addressBookTests();
};

#endif // DIGIBYTE_QT_TEST_ADDRESSBOOKTESTS_H
