#include <entityx/entityx.h>

struct Movement : public entityx::System<Movement> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<Position>([dt](entityx::Entity entity, Position &position) {
			CCLOG("Test");
		});
	};
};