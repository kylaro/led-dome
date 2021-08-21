#include "EffectEngine.h"


EffectEngine::EffectEngine() {

}

void EffectEngine::clear() {
    effects.clear();
}

void EffectEngine::apply(Effect * effect) {
	effects.push_back(effect);
}

void EffectEngine::run() {
    std::vector<Effect *>::iterator it = effects.begin();
    while (it != effects.end())
    {
        Effect* eff = *it;
        if (eff->done ) {
            // erase() invalidates the iterator, use returned iterator
            it = effects.erase(it);
            continue;
        } else {
            ++it;
        }

        eff->run();
    }
}
