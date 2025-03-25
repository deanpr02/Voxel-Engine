#include "weapon.h"

WeaponSystem::WeaponSystem(){
    Lightning* spell_a = new Lightning();
    m_spells = std::vector<Spell*>{spell_a};
    m_currentSpell = m_spells[0];
}

void WeaponSystem::spawn(glm::vec3 origin, glm::vec3 dir, glm::vec3 right){
    int random = -m_currentSpell->spellRadius + (std::rand() % (m_currentSpell->spellRadius * 2 + 1));
    for(int i=0;i<m_currentSpell->spellDensity;i++){
        float randomX = (-m_currentSpell->spellRadius + (std::rand() % (m_currentSpell->spellRadius * 2 + 1)))*0.02;
        float randomY = (-m_currentSpell->spellRadius + (std::rand() % (m_currentSpell->spellRadius * 2 + 1)))*0.02;
        glm::vec3 offsetOrigin = origin + (right*randomX);
        offsetOrigin += glm::vec3(0,randomY,0);
        Particle p = Particle(offsetOrigin,dir);
        m_currentSpell->m_particles.push_back(p);
    }
}


