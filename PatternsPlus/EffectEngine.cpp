#include "EffectEngine.h"


EffectEngine::EffectEngine() {

}

void EffectEngine::clear() {
    for (Effect* eff : effects) {
        eff->release();
    }
    run();
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
            //free(eff);
            continue;
        } else {
            ++it;
        }

        eff->run();
    }
}
