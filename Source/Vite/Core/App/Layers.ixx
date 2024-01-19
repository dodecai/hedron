export module Vite.App.Layers;

import Vite.Base;
import Vite.Event;

export namespace Hedron {

///
/// @brief Simple Application Layer Implementation
///
class Layer {
public:
    /// Default
    Layer(const string &name = "Layer"): mName(name) {}
    virtual ~Layer() = default;

    ///
    /// Interface
    ///
    
    virtual void Create() {}
    virtual void Destroy() {}
    virtual void Attach() {}
    virtual void Detach() {}
    virtual void GuiUpdate() {}
    virtual void Update(DeltaTime deltaTime) {}

    ///
    /// Event Interface
    ///

    virtual void OnAppEvent(const WindowEvent &event /*, const EventListener::EventEmitter &emitter */) {}
    virtual void OnInputEvent(const ControllerEvent &event /*, const EventListener::EventEmitter &emitter */) {}
    virtual void OnInputEvent(const KeyboardEvent &event /*, const EventListener::EventEmitter &emitter */) {}
    virtual void OnInputEvent(const MouseEvent &event/*, const EventListener::EventEmitter &emitter */) {}
    virtual void OnInputEvent(const TouchEvent &event /*, const EventListener::EventEmitter &emitter */) {}
    
    /// Accessors
    const string &GetName() const { return mName; }
    
protected:
    /// Properties
    string mName;
};

///
/// @brief Container for the Application Layers
///
class LayerStack {
public:
    /// Default
    LayerStack() = default;
    ~LayerStack() {
        for (auto *layer : mLayers) {
            layer->Detach();
            delete layer;
        }
    }

    /// Methods
    void PushLayer(Layer *layer) {
        mLayers.emplace(mLayers.begin() + mLayerInsertIndex, layer);
        mLayerInsertIndex++;
        layer->Attach();
    }
    void PushOverlay(Layer *overlay) {
        mLayers.emplace_back(overlay);
        overlay->Attach();
    }
    void PopLayer(Layer *layer) {
        auto it = std::find(mLayers.begin(), mLayers.begin() + mLayerInsertIndex, layer);
        if (it != mLayers.begin() + mLayerInsertIndex) {
            layer->Detach();
            mLayers.erase(it);
            mLayerInsertIndex--;
        }
    }
    void PopOverlay(Layer *overlay) {
        auto it = std::find(mLayers.begin() + mLayerInsertIndex, mLayers.begin(), overlay);
        if (it != mLayers.begin() + mLayerInsertIndex) {
            overlay->Detach();
            mLayers.erase(it);
        }
    }

    /// Iterators
    auto begin() { return mLayers.begin(); }
    auto end() { return mLayers.end(); }
    auto rbegin() { return mLayers.rbegin(); }
    auto rend() { return mLayers.rend(); }

    auto begin() const { return mLayers.begin(); }
    auto end() const { return mLayers.end(); }
    auto rbegin() const { return mLayers.rbegin(); }
    auto rend() const { return mLayers.rend(); }

private:
    /// Properties
    uint32 mLayerInsertIndex = 0;
    vector<Layer *> mLayers;
};

}
