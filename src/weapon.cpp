#include "weapon.h"

WeaponSystem::WeaponSystem(Camera* camera){
    Lightning* spell_a = new Lightning(camera->getViewMatrix());
    m_spells = std::vector<Spell*>{spell_a};
    m_currentSpell = m_spells[0];
}

void WeaponSystem::spawn(glm::vec3 origin, glm::vec3 dir, glm::vec3 right,glm::mat4 viewMatrix){
    m_currentSpell->summon(origin,dir,right,viewMatrix);
}


