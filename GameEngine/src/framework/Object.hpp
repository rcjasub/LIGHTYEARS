#pragma once

#include "Core.hpp"
#include "Delegate.hpp"
#include <memory>
#include <string>

namespace ly
{
    class World;
    class Object : public std::enable_shared_from_this<Object>
    {
        public:
            Object() = delete;
            explicit Object(const std::string& name);
            virtual ~Object();

            virtual void Destroy();
            [[nodiscard]] bool IsPendingDestroy() const {return mIsPendingDestroy;};

            weak<Object> GetSelfWeakSRef();
            weak<const Object> GetSelfWeakSRef() const;
            Delegate<Object*> OnDestroy;
            [[nodiscard]] unsigned int GetUniqueId() const {return mUniqueID;}
        protected:
            [[nodiscard]] inline std::string const& GetActorName() const {return mName;}
        private:
            bool mIsPendingDestroy;
            uint64_t mUniqueID;
            static uint64_t smUniqueID_counter;
            static uint64_t GetNextAvailableID();
            const std::string mName;
    };
}
