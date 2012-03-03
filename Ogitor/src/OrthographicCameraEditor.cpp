
#include "OgitorsPrerequisites.h"
#include "BaseEditor.h"
#include "OgitorsRoot.h"
#include "OgitorsSystem.h"
#include "VisualHelper.h"
#include "CameraVisualHelper.h"
#include "ViewportEditor.h"
#include "CameraEditor.h"
#include "OrthographicCameraEditor.h"
#include <OgreCamera.h>

using namespace Ogitors;
    
TiXmlElement* COrthographicCameraEditor::exportDotScene(TiXmlElement *pParent)
{

}
    
bool COrthographicCameraEditor::load(bool async) {
    CCameraEditor::load(async);
    Ogre::Camera* camera = mHandle;
    camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
}

void COrthographicCameraEditor::setViewMode(int value) {
    Ogre::Quaternion rotation;
    Ogre::Quaternion z(Ogre::Degree(-90), Ogre::Vector3::UNIT_Z); 
    Ogre::Quaternion x(Ogre::Degree(-90), Ogre::Vector3::UNIT_X); 
    Ogre::Quaternion result(x * z);
    switch (value) {
        case 0 :
            break;
        case 1 : // Face north.
            rotation = Ogre::Quaternion(sqrt(0.5), -sqrt(0.5), 0, 0); 
            setOrientation(rotation);
            break;
        case 2 : // Face East 
            rotation = Ogre::Quaternion(0.5, -0.5, 0.5, 0.5); 
            setOrientation(result);
            break;
        case 3 :  // Face South
            rotation = Ogre::Quaternion(0, 0, sqrt(0.5), sqrt(0.5)); 
            setOrientation(rotation);
            break;
        case 4 :  // Face West
            rotation = Ogre::Quaternion(0.5, -0.5, -0.5, -0.5); 
            setOrientation(rotation);
            break;
    }
}

COrthographicCameraEditorFactory::COrthographicCameraEditorFactory(OgitorsView *view) : CCameraEditorFactory(view) {
    mTypeName = "Orthographic Camera Object";
}

//-----------------------------------------------------------------------------------------
CBaseEditor *COrthographicCameraEditorFactory::CreateObject(CBaseEditor **parent, OgitorsPropertyValueMap &params)
{
    COrthographicCameraEditor *object = OGRE_NEW COrthographicCameraEditor(this);

    OgitorsPropertyValueMap::iterator ni;

    if ((ni = params.find("init")) != params.end())
    {
        OgitorsPropertyValue value = EMPTY_PROPERTY_VALUE;
        value.val = Ogre::Any(CreateUniqueID("OrthographicCamera"));
        params["name"] = value;
        params.erase(ni);
    }
    
     OgitorsPropertyValue value;
    value.propType = PROP_STRING;
    value.val = Ogre::Any(Ogre::StringConverter::toString("OrthographicCamera"));
    params["name"] = value;
    value.propType = PROP_VECTOR3;
    value.val = Ogre::Any(Ogre::Vector3(0,1000,0));
    params["position"] = value;
    value.propType = PROP_QUATERNION;
    value.val = Ogre::Any(Ogre::Quaternion(sqrt(0.5), -sqrt(0.5), 0, 0));
    params["orientation"] = value;

    object->createProperties(params);
    object->mParentEditor->init(*parent);
    object->registerForPostSceneUpdates();
    mInstanceCount++;
    return object;
}
