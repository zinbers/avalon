#include <avalon/physics/CollisionManager.h>

namespace avalon {
namespace physics {

CollisionManager::CollisionManager(Box2dContainer& box2dContainer)
: box2dContainer(box2dContainer)
{
    contactContainer.container = &box2dContainer;
}

void CollisionManager::BeginContact(b2Contact* contact)
{
    contactContainer.contact = contact;
    auto handled = false;

    for (auto& callback : listBeginContact) {
        handled = callback(contactContainer) || handled;
    }

    if (!handled && fallback) {
        fallback->onBeginContact(contactContainer);
    }
}

void CollisionManager::EndContact(b2Contact* contact)
{
    contactContainer.contact = contact;
    auto handled = false;

    for (auto& callback : listEndContact) {
        handled = callback(contactContainer) || handled;
    }

    if (!handled && fallback) {
        fallback->onEndContact(contactContainer);
    }
}

void CollisionManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    contactContainer.contact = contact;
    auto handled = false;

    for (auto& callback : listPreSolve) {
        handled = callback(contactContainer, *oldManifold) || handled;
    }

    if (!handled && fallback) {
        fallback->onPreSolve(contactContainer, *oldManifold);
    }
}

void CollisionManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    contactContainer.contact = contact;
    auto handled = false;
    
    for (auto& callback : listPostSolve) {
        handled = callback(contactContainer, *impulse) || handled;
    }

    if (!handled && fallback) {
        fallback->onPostSolve(contactContainer, *impulse);
    }
}

} // namespace physics
} // namespace avalon