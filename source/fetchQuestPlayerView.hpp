#pragma once

#include <renderer/scene_nodes/orthographicCameraNode.hpp>
#include <renderer/scene_nodes/perspectiveCameraNode.hpp>
#include <views/humanView.hpp>

class FetchQuestPlayerView: public HumanView
{
public:
	FetchQuestPlayerView(std::shared_ptr<IRenderer> renderer,
		std::shared_ptr<platypus::IResourceCache> cache, const platypus::Settings& settings)
		: HumanView(renderer, cache, settings)
	{}

	virtual ~FetchQuestPlayerView() = default;

private:
	std::shared_ptr<platypus::CameraNode> createCamera() override
	{
		return this->createOrthographicCamera();
	}
	std::shared_ptr<platypus::PerspectiveCameraNode> createPerspectiveCamera()
	{
		SceneNodeData node_data;
		node_data.name = "camera";
		node_data.render_pass = RenderPass::First;
		platypus::PerspectiveCameraNodeData camera_node_data;
		camera_node_data.base_node_data = &node_data;
		camera_node_data.frustum.initialize(3.1415f / 4.0f, 1.0f, 1.0f, 1000.0f);
		camera_node_data.frustum.setAspect(1280.0 / 720);
		camera_node_data.offset_vector = {0.0f, 0.0f, -10.0f, 0.0f};

		return std::make_shared<platypus::PerspectiveCameraNode>(camera_node_data);
	}
	std::shared_ptr<platypus::OrthographicCameraNode> createOrthographicCamera()
	{
		SceneNodeData node_data;
		node_data.name = "camera";
		node_data.render_pass = RenderPass::First;
		platypus::OrthographicCameraNodeData camera_node_data;
		camera_node_data.base_node_data = &node_data;
		camera_node_data.dimensions = {720, 1280};
		camera_node_data.near_z = 0;
		camera_node_data.far_z = 100;

		return std::make_shared<platypus::OrthographicCameraNode>(camera_node_data);
	}
};
