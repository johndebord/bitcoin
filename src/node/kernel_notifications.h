// Copyright (c) 2023 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_NODE_KERNEL_NOTIFICATIONS_H
#define BITCOIN_NODE_KERNEL_NOTIFICATIONS_H

#include <kernel/notifications_interface.h>

#include <atomic>
#include <cstdint>
#include <string>

class CBlockIndex;
enum class SynchronizationState;
struct bilingual_str;

namespace node {
class KernelNotifications : public kernel::Notifications
{
public:
    KernelNotifications(std::atomic<int>& exit_status) : m_exit_status{exit_status} {}

    void blockTip(SynchronizationState state, CBlockIndex& index) override;

    void headerTip(SynchronizationState state, int64_t height, int64_t timestamp, bool presync) override;

    void progress(const bilingual_str& title, int progress_percent, bool resume_possible) override;

    void warning(const bilingual_str& warning) override;

    void flushError(const std::string& debug_message) override;

    void fatalError(const std::string& debug_message, const bilingual_str& user_message = {}) override;

    //! Useful for tests, can be set to false to avoid shutdown on fatal error.
    bool m_shutdown_on_fatal_error{true};
private:
    std::atomic<int>& m_exit_status;
};
} // namespace node

#endif // BITCOIN_NODE_KERNEL_NOTIFICATIONS_H