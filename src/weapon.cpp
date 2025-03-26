#include "weapon.h"

WeaponSystem::WeaponSystem(){
    Lightning* spell_a = new Lightning();
    m_spells = std::vector<Spell*>{spell_a};
    m_currentSpell = m_spells[0];
}

void WeaponSystem::spawn(glm::vec3 origin, glm::vec3 dir, glm::vec3 right){
    m_currentSpell->summon(origin,dir,right);
}


