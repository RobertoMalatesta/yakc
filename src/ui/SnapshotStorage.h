#pragma once
//------------------------------------------------------------------------------
/**
    @class SnapshotStorage
    @brief simple class to store machine state snapshots
*/
#include "yakc/KC85Oryol.h"

class SnapshotStorage {
public:
    /// max number of snapshots
    static const int MaxNumSnapshots = 4;

    /// constructor
    SnapshotStorage();
    /// take a snapshot
    void TakeSnapshot(const yakc::emu& emu, int slotIndex);
    /// test if any valid snapshots exist
    bool HasSnapshots() const;
    /// test if a snapshot slot contains a snapshot
    bool HasSnapshot(int slotIndex) const;
    /// apply a snapshot
    void ApplySnapshot(int slotIndex, yakc::emu& emu);

    yakc::kc85_snapshot::state_t snapshots[MaxNumSnapshots];
};