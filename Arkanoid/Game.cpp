//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "RendererData.h"
#include "WorldHelper.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
	m_deviceResources->CreateWindowSizeDependentResources();

	FontManager::Instance()->Init(m_deviceResources->GetD3DDevice());
	TextureManager::Instance()->Init(m_deviceResources->GetD3DDevice());
    InputHandler::Instance()->Init(window);
    
    State = std::make_unique<PlayState>();
    State->OnEnter();

    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    State->FixedUpdate();

    m_timer.Tick([&]()
    {
        Update(m_timer);
    });
    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    InputHandler::Instance()->Update(elapsedTime);
    State->Update(elapsedTime);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	context->RSSetState(m_states->CullNone());

	m_effect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

    RendererData RenderData(m_batch.get(), m_primitiveBatch.get());
    
    State->Render(RenderData);

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
    InputHandler::Instance()->Reset();
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    InputHandler::Instance()->Reset();
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;

	RECT GameBounds;
	GameBounds.left = 0;
	GameBounds.right = width;
	GameBounds.top = 0;
	GameBounds.bottom = height;
	WorldHelper::Instance()->SetGameBounds(GameBounds);
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_states = std::make_unique<CommonStates>(device);
	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);

	m_batch = std::make_unique<SpriteBatch>(context);
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexType>>(context);


	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexType>(device, m_effect.get(),
			m_inputLayout.ReleaseAndGetAddressOf())
	);

	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexType>>(context);

    State->OnCreateResources();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
	auto size = m_deviceResources->GetOutputSize();
	
    Matrix m_world = Matrix::CreateTranslation(float(size.right) / 2.f, float(size.bottom) / 2.f, 0.f);
    WorldHelper::Instance()->SetWorldMatrix(m_world);

    RECT CurrentGameBounds = WorldHelper::Instance()->GetGameBounds();

    RECT GameBounds;
    GameBounds.left = size.left;
    GameBounds.right = size.right;
    GameBounds.top = size.top;
    GameBounds.bottom = size.bottom;
    WorldHelper::Instance()->SetGameBounds(GameBounds);

    //transform normalized space of primitive batch in pixel space
	Matrix proj = Matrix::CreateScale(2.f / float(size.right),
		-2.f / float(size.bottom), 1.f)
		* Matrix::CreateTranslation(-1.f, 1.f, 0.f);
    proj = WorldHelper::Instance()->GetWorldMatrix() * proj;
	m_effect->SetProjection(proj);

    float xRatio = 1;
    float yRatio = 1;
    if (CurrentGameBounds.right != 0)
    {
        xRatio = float(GameBounds.right) / float(CurrentGameBounds.right);
    }
	if (CurrentGameBounds.bottom != 0)
	{
        yRatio = float(GameBounds.bottom) / float(CurrentGameBounds.bottom);
	}
    State->OnWindowSizeUpdate(xRatio, yRatio);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
	m_states.reset();
	m_effect.reset();
	m_batch.reset();
	m_primitiveBatch.reset();

	m_inputLayout.Reset();
    
    State->OnReleaseResources();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
