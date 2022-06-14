#include "CloseState.hpp"

#include "../ServerConfiguration/Configuration.hpp"

CloseState::CloseState ()  {}

void CloseState::handle (void) {
    context->setClose ();
	Configuration::instance ()->getLogger ().AccessLog ("Close", *(this->context));
}
