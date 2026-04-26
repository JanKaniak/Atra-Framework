#include "NumericInput.h"

// Class IntSlider
void IntSlider::draw(std::vector<Message> &messageHistory)
{
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}

// Class IntVSlider
void IntVSlider::draw(std::vector<Message> &messageHistory)
{

    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(), ImVec2(30, 100), attribute_->getDescription()->getDataType(),&value_, &minimum_ ,&maximum_))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
}


// Class IntDrag
void IntDrag::draw(std::vector<Message> &messageHistory)
{
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attribute_->getMinimum(), attribute_->getMaximum()))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), attribute_->getDescription()->getDataType(), &value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class DoubleVSlider
void DoubleVSlider::draw(std::vector<Message> &messageHistory) {
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),size,attribute_->getDescription()->getDataType(),&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    } 
    dimensions_ = ImGui::GetItemRectSize();
}



// Class DoubleDrag
void DoubleDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),attribute_->getDescription()->getDataType(),&value_,0.5f, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

//---------------------------------------------------------------------------------------



// Class FloatSlider
void FloatSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderFloat(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class FloatVSlider
void FloatVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    
    if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),size,&value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class FloatDrag
void FloatDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragFloat(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }


//---------------------------------------------------------------------------------------



// Class CharSlider
void CharSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class CharVSlider
void CharVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class CharDrag
void CharDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------


// Class LongSlider
void LongSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class LongVSlider
void LongVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class LongDrag
void LongDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

 //--------------------------------------------------------------------------------------


// Class UintSlider
void UintSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class UintVSlider
void UintVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class UintDrag
void UintDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }
